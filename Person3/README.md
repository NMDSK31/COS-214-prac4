# EventForge - COS 214 Practical 4

> Person 3 integration draft: move this file and the accompanying build files
> to the repository root during final integration. The commands below apply to
> that final layout.

EventForge is a C++11 university event-planning system created for the
TaskForge practical. It models an event as a recursive work hierarchy and
combines the Composite, Iterator, State, and Decorator design patterns in one
integrated application.

## Team contribution

- Keval Govind (`u24904407`) - Person 3: Iterator, integration, and build tooling
- Remaining team details will be added before submission.

## Required tools

The project can be built directly with a C++11 compiler and GNU Make, or inside
Docker. The Docker image also contains GDB and Valgrind so no project-specific
debugging tools need to be installed on the host machine.

## Build and run on the host

```sh
make
./taskforge
```

The executable is always named `taskforge`.

Available Make targets:

```sh
make          # Build taskforge
make run      # Build and run the application
make valgrind # Build and run the Valgrind memory investigation
make clean    # Remove generated objects, dependency files, and executable
```

## Build and run with Docker

Build the reproducible development image from the repository root:

```sh
docker build -t eventforge-taskforge .
docker run --rm eventforge-taskforge
```

## Use GDB inside Docker

Start an interactive container with the permissions required for debugging:

```sh
docker run --rm -it \
  --cap-add=SYS_PTRACE \
  --security-opt seccomp=unconfined \
  eventforge-taskforge bash
```

Then run:

```sh
gdb ./taskforge
```

Useful GDB commands for the required investigation include:

```text
break DepthFirstIterator::next
run
next
print expectedVersion
continue
quit
```

The final submission will record a genuine bug, the inspected program state,
its cause, and the correction made during development.

## Run Valgrind inside Docker

From the same interactive container:

```sh
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

The final application must contain no definitely-lost memory originating from
project code.

## Intended final repository structure

```text
include/
  core/
  decorator/
  domain/
  iterator/
  state/
  task/
src/
  core/
  decorator/
  domain/
  iterator/
  state/
  task/
docs/
main.cpp
Makefile
Dockerfile
README.md
```

During development, each team member works in their assigned `PersonN/`
folder. The completed files will be integrated into the final structure before
submission.

## Iterator subsystem tests in the development layout

From the repository root, run the normal and sanitizer-backed test suites with:

```sh
make -C Person3/tests test
make -C Person3/tests sanitize
make -C Person3/tests clean
```

The sanitizer target uses UndefinedBehaviorSanitizer. The development tests
use Person 1's real composite implementation and a controlled task leaf. They
will be supplemented with Person 2's concrete `EventTask` and checked with
Valgrind inside Docker during final integration.
