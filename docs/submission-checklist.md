# Final submission checklist

This audit separates verified repository requirements from material that must
still be supplied or approved by the full team.

## Verified in the repository

- [x] C++11 source and headers for Composite, Iterator, State and Decorator.
- [x] Recursive hierarchy with at least three levels below the client/root.
- [x] Independent full and incomplete-work iterators.
- [x] Safe iterator invalidation after structural mutation.
- [x] State changes do not invalidate traversal.
- [x] Valid and invalid lifecycle transitions.
- [x] Two stackable runtime decorators with an owning wrapper chain.
- [x] Connected `main.cpp` story rather than a pattern-by-pattern menu.
- [x] Runtime detach, move, decorate and reattach scenario.
- [x] Root `Makefile` produces the `taskforge` executable without warnings.
- [x] Normal and UndefinedBehaviorSanitizer regression tests pass.
- [x] Docker performs a clean Linux compilation and runs the application.
- [x] GDB breakpoint and live-state inspection verified inside Docker.
- [x] Valgrind reports zero errors and no remaining heap allocations.
- [x] README contains host, Docker, GDB and Valgrind commands.
- [x] Git history contains meaningful contributions from all three members.

## Required before final submission

- [ ] Add Person 1 and Person 2 student numbers to the README and final PDF.
- [ ] Review the final class diagram against the submitted headers, including
      protected traversal hooks and decorator ownership.
- [ ] Export the final class, object and EventTask state diagrams.
- [ ] Export three final activity diagrams with the required guards, loops,
      fork/join, called activity and swimlanes.
- [ ] Capture readable screenshots of the genuine GDB and Valgrind runs.
- [ ] Replace preparation/template text in the design specification with the
      actual investigation, GitHub reflection and contribution statement.
- [ ] Assemble and visually review the final submission PDF.
- [ ] Have all three members review the runtime story and ownership policy.
- [ ] Push the reviewed commits to GitHub and confirm repository access.
- [ ] Produce the final source archive from the committed repository state.
