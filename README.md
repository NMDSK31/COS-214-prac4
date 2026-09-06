# EventForge - COS 214 Practical 4

EventForge is a C++11 university event-planning system created for the
TaskForge practical. It models an event as a recursive hierarchy and combines
the Composite, Iterator, State and Decorator design patterns in one connected
runtime story.

## Team contribution

- Ntando - Person 1: Composite hierarchy and ownership
- Lukuna Kabongo - Person 2: EventTask, State and Decorator
- Keval Govind (`u24904407`) - Person 3: Iterator, integration and build tooling

## Build and run on the host

A C++11 compiler and GNU Make are required:

```sh
make
./taskforge
```

The executable is always named `taskforge`. Other useful targets are:

```sh
make run       # Build and run the connected demonstration
make valgrind  # Run the executable under Valgrind when it is installed
make clean     # Remove generated objects, dependencies and executables
```

Run the integration and iterator regression tests with:

```sh
make test
make sanitize
make -C tests clean
```

## Docker

The image includes `g++`, Make, GDB and Valgrind:

```sh
docker build -t eventforge-taskforge .
docker run --rm eventforge-taskforge
```

Run the final memory investigation inside the Linux image:

```sh
docker run --rm eventforge-taskforge \
  valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

For an interactive GDB session:

```sh
docker run --rm -it \
  --cap-add=SYS_PTRACE \
  --security-opt seccomp=unconfined \
  eventforge-taskforge bash
gdb ./taskforge
```

A useful investigation point is `DepthFirstIterator::next`. Its
`expectedVersion` can be compared with the hierarchy's live
`StructureVersion` after a task is moved.

The verified detach investigation uses:

```text
(gdb) break WorkGroup::detachChild
(gdb) run
(gdb) print childID
(gdb) print children.size()
```

## Runtime story

The demonstration builds an Open Day hierarchy with four nested levels. It
then:

1. advances two independent depth-first iterators;
2. demonstrates an invalid and a valid task-state transition;
3. detaches and moves a task between task lists;
4. stacks urgent and approval decorators around the moved task;
5. shows that the structural change invalidates an existing iterator;
6. recreates the traversal and reports only incomplete work.

`WorkGroup` owns its direct children. A decorator owns its wrapped task or
decorator, `EventTask` owns its current state, and iterator pointers are
non-owning. Structural changes bump the shared version and invalidate existing
iterators before stale hierarchy pointers are dereferenced. State-only changes
do not invalidate traversal.

## Repository structure

```text
include/
  core/       Composite abstractions and structure version
  domain/     EventPlan hierarchy types
  task/       ExecutableTask and EventTask
  state/      Task lifecycle states
  decorator/  Runtime task decorators
  iterator/   Independent hierarchy traversals
src/          Matching implementations
tests/        Iterator and integration regression suite
docs/         Design material and UML exports
main.cpp      Connected demonstration
Makefile
Dockerfile
README.md
```
