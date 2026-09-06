#ifndef WORK_ITERATOR_H
#define WORK_ITERATOR_H

class WorkComponent;

/**
 * @brief Interface for traversing the EventForge work hierarchy.
 *
 * Iterators expose non-owning WorkComponent pointers and never own or delete
 * the hierarchy being traversed.
 */
class WorkIterator {
public:
    virtual ~WorkIterator() {}

    /** Reset the traversal to its first eligible component. */
    virtual void first() = 0;

    /** Advance to the next eligible component. */
    virtual void next() = 0;

    /** Return true when no eligible current component remains. */
    virtual bool isDone() const = 0;

    /** Return the current component without transferring ownership. */
    virtual WorkComponent* current() const = 0;

    /** Return false when a structural change invalidates the traversal. */
    virtual bool isValid() const = 0;
};

#endif
