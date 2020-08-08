# Network Namespace Wrapper

This is a simple C application that will allow you to launch any binary in a specified network namespace. It is intended to be used to allow an unprivileged user to run a specified application in a specified network namespace.

### Compilation/Installation

This application takes arguments at compile-time. You must set the define variables for `NAMESPACE` and `BINARY`. `NAMESPACE` is a string of the name of your network namespace, as reported by `ip netns`. `BINARY` is a string of the path to the binary you want to run in a separate namespace.

```bash
gcc -D 'NAMESPACE="my_namespace"' -D 'BINARY="/usr/bin/bash"' -o bash-wrapped main.c
install -m 4755 -o 0 -g 0 bash-wrapped /usr/local/bin/bash-wrapped
```

### Security

Use this at your own risk, and if you are concerned about a security issue, please audit the source code yourself and report any bugs.

The application you run has no restricted permissions compared to any other applications on the system, except the network namespace it is in. This means the application may launch other applications within the network namespace. You should not make the assumption that the application run in the namespace is the only application able to run in the namespace.