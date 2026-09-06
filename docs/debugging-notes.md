# Engineering investigation notes

These notes record genuine checks performed on 6 September 2026. They provide
source material for the final PDF; the team must still capture and include the
required screenshots.

## Docker build-context bug

Symptom: the first image build reported `Nothing to be done for 'all'` because
host build outputs had entered the Docker context. After an initial ignore rule
was added, the Linux linker then rejected `src/core/StructureVersion.o` with
`file format not recognized`.

Cause: the first `.dockerignore` used `*.o` and `*.d`, which did not exclude
object and dependency files nested below `src/` in this Docker setup. The image
therefore received macOS ARM object files instead of compiling all sources in
Ubuntu.

Correction: recursive `**/*.o`, `**/*.d`, `**/*.out` and `**/*.dSYM` patterns
were added. The next image build compiled every source with Linux `g++` and
completed successfully without warnings.

## GDB inspection

GDB was run inside the final Docker image with a breakpoint at
`WorkGroup::detachChild`. At the breakpoint:

- `childID` was `"setup-sound"`;
- `children.size()` was `2` before detachment; and
- execution continued to normal program termination.

The exact command was:

```sh
docker run --rm \
  --cap-add=SYS_PTRACE \
  --security-opt seccomp=unconfined \
  eventforge-taskforge \
  gdb -q -batch \
    -ex 'break WorkGroup::detachChild' \
    -ex run \
    -ex 'print childID' \
    -ex 'print children.size()' \
    -ex continue \
    ./taskforge
```

## Valgrind result

Valgrind 3.18.1 ran against the final containerized executable. It reported:

```text
in use at exit: 0 bytes in 0 blocks
total heap usage: 93 allocs, 93 frees, 84,360 bytes allocated
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```
