#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  // Set the prompt.
  char *prompt = "simple_shell> ";

  // Create a buffer to store the user's input.
  char buffer[1024];

  // Loop forever until the user exits the shell.
  while (1) {
// Display the prompt.
printf("%s", prompt);

// Read the user's input.
fgets(buffer, sizeof(buffer), stdin);

// Check if the user has entered the "end of file" character.
if (feof(stdin)) {
  // Exit the shell.
  break;
}

// Remove the newline character from the end of the input.
buffer[strlen(buffer) - 1] = '\0';

// Try to find the executable for the command.
char *executable = getenv("PATH");
while (executable != NULL) {
  // Split the PATH environment variable into directories.
  char *directory = strtok(executable, ":");

  // Concatenate the directory and the command to form the full path to the executable.
  char path[1024];
  sprintf(path, "%s/%s", directory, buffer);

  // If the executable exists, execute it.
  if (access(path, X_OK) == 0) {
// Execute the command.
execve(path, NULL, environ);

// If the execution fails, print an error message.
perror("execve");
break;
  }

  // Move on to the next directory in the PATH environment variable.
  executable = strtok(NULL, ":");
}

// If the executable cannot be found, print an error message.
if (executable == NULL) {
  printf("Command not found: %s\n", buffer);
}
  }

  // Exit the shell.
  return 0;
}
