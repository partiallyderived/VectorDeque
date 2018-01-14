#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <string>

/**
 * `VectorDeque` satisfies the resource constraints typically expected of both Vectors and Deques. In particular, it has
 *
 * * `O(1)` Member access
 * * `O(1)` Append
 * * `O(1)` Prepend
 *
 * Additionally, `VectorDeque` will only automatically resize when it is at full capacity.
 * Iterators for `VectorDeque` maintain an index to the element they are currently pointing to, and modifications
 * to the `VectorDeque` will not change that index. For example, suppose an element is added to the front of the
 * `VectorDeque` while an iterator is pointing to the third element. That iterator will now be pointing to what was
 * previously the second element, since that element is not the third element and the iterator's index did not change.
 * @param DataType The type of the data to contain.
 */
template <class DataType>
class VectorDeque {
    private:
    // Allow testing class to access private methods and fields.
    friend class VectorDequeTest;

    // Base class for the mutable and immutable iterator implementations.
    template <class VectorDequeType, class MemberType, bool IS_REVERSE>
    class IteratorBase {
        typedef IteratorBase<VectorDeque, DataType, IS_REVERSE> Iterator;
        typedef IteratorBase<const VectorDeque, const DataType, IS_REVERSE> ConstIterator;
        friend VectorDeque;

        private:
        // Position in the VectorDeque this iterator is pointing to.
        size_t _position;

        // Pointer to VectorDeque this iterator is iterating on.
        VectorDequeType* const _vectorDequePtr;

        static MemberType& dereferenceAt(VectorDequeType* const vectorDequePtr, const ptrdiff_t position) throw() {
            if (IS_REVERSE) {
                return (*vectorDequePtr)[vectorDequePtr->size() - position - 1];
            }
            return (*vectorDequePtr)[position];
        }

        public:
        // Constructs an Iterator from a VectorDeque pointer and a position.
        IteratorBase(VectorDequeType* const vectorDequePtr, const size_t position) throw():
                _vectorDequePtr(vectorDequePtr), _position(position) {}

        // Constructs an Iterator from a VectorDeque pointer.
        IteratorBase(VectorDequeType* const vectorDequePtr) throw(): _vectorDequePtr(vectorDequePtr), _position(0) {}

        /**
         * Construct an iterator which is not pointing to anything.
         * Runtime: `O(1)`
         */
        IteratorBase() throw(): _position(0), _vectorDequePtr(NULL) {}

        /**
         * Construct an iterator by copying the state of another iterator.
         * Runtime: `O(1)`
         * @param that Iterator to copy the state from.
         */
        IteratorBase(const Iterator& that) throw(): _position(that._position), 
        _vectorDequePtr(that._vectorDequePtr) {}

        /**
         * Construct an iterator by copying the state of another iterator.
         * Runtime: `O(1)`
         * @param that Iterator to copy the state from.
         */
        IteratorBase(const ConstIterator& that) throw(): _position(that._position), 
                _vectorDequePtr(that._vectorDequePtr) {}

        /**
         * Copy the state of `that` into `*this`.
         * Runtime: `O(1)`
         * @param that Iterator to copy the state from.
         * @return A reference to `*this`.
         */
        IteratorBase& operator =(const Iterator& that) throw() {
            _position = that._position;
            _vectorDequePtr = that._vectorDequePointer;
            return *this;
        }

        /**
         * Copy the state of `that` into `*this`.
         * Runtime: `O(1)`
         * @param that Iterator to copy the state from.
         * @return A reference to `*this`.
         */
        IteratorBase& operator =(const ConstIterator& that) throw() {
            _position = that._position;
            _vectorDequePtr = that._vectorDequePointer;
            return *this;
        }

        /**
         * Convert `*this` to a constant iterator.
         * Runtime: `O(1)`
         * @return An immutable copy of `*this`.
         *
        operator ConstIterator() const throw() {
            return ConstIterator(*this);
        }
        */

        /**
         * Check for equality with another iterator.
         * Runtime: `O(1)`
         * @param that Iterator to check for equality with.
         * @return `true` If `*this` and `that` are iterating over the same object at the same position and 
         *          direction, `false` otherwise.
         */
        bool operator ==(const ConstIterator& that) const throw() {
            return _position == that._position && _vectorDequePtr == that._vectorDequePtr;
        }

        /**
         * Check for inequality with another iterator.
         * Runtime: `O(1)`
         * @param that Iterator to check for inequality with.
         * @return `true` If `*this` and `that` are iterating over different objects or at different positions, 
         *         `false` otherwise.
         */
        bool operator !=(const ConstIterator& that) const throw() {
            return !(*this == that);
        }

        /**
         * Check to see if `*this` is pointing to an earlier element than `that`.
         * Runtime: `O(1)`
         * @param that Iterator to compare against.
         * @return `true` If `*this` points to an earlier element than `that` and `*this != that`, `false` 
         *         otherwise.
         */
        bool operator <(const ConstIterator& that) const throw() {
            return _position < that._position;
        }

        /**
         * Check to see if `*this` is pointing to a later element than `that`.
         * Runtime: `O(1)`
         * @param that Iterator to compare against.
         * @return `true` If `*this` points to a later element than `that` and `*this != that`, `false` 
         *         otherwise.
         */
        bool operator >(const ConstIterator& that) const throw() {
            return _position > that._position;
        }

        /**
         * Check to see if `*this` is pointing to an earlier element than `that` or if they are pointing at the
         * same element.
         * Runtime: `O(1)`
         * @param that Iterator to compare against.
         * @return `true` If `*this` points to an earlier element than `that` or `*this == that`, `false` 
         *         otherwise.
         */
        bool operator <=(const ConstIterator& that) const throw() {
            return *this == that || *this < that;
        }

        /**
         * Check to see if `*this` is pointing to a later element than `that` or if they are pointing at the
         * same element.
         * Runtime: `O(1)`
         * @param that Iterator to compare against.
         * @return `true` If `*this` points to a later element than `that` or `*this == that`, `false` 
         *         otherwise.
         */
        bool operator >=(const ConstIterator& that) const throw() {
            return *this == that || *this > that;
        }

        /**
         * Increment the position of `*this`.
         * Runtime: `O(1)`
         * @return A reference to `*this`.
         */
        IteratorBase& operator ++() throw() {
            ++_position;
            return *this;
        }

        /**
         * Increment the position of `*this`.
         * Runtime: `O(1)`
         * @return A copy of `*this` before incrementation.
         */
        IteratorBase operator ++(int) throw() {
            const IteratorBase copy(*this);
            ++_position;
            return copy;
        }

        /**
         * Decrement the position of `*this`.
         * Runtime: `O(1)`
         * @return A reference to `*this`.
         */
        IteratorBase& operator --() throw() {
            --_position;
            return *this;
        }

        /**
         * Decrement the position of `*this`.
         * Runtime: `O(1)`
         * @return A copy of `*this` before decrementation.
         */
        IteratorBase operator --(int) throw() {
            const IteratorBase copy(*this);
            --_position;
            return copy;
        }

        /**
         * Advance the position of `*this` by `amount`.
         * Runtime: `O(1)`
         * @param amount Amount to advance by.
         * @return A reference to `*this`.
         */
        IteratorBase& operator +=(const ptrdiff_t amount) throw() {
            _position += amount;
            return *this;
        }

        /**
         * Regress the position of `*this` by `amount`.
         * Runtime: `O(1)`
         * @param amount Amount to regress by.
         * @return A reference to `*this`.
         */
        IteratorBase& operator -=(const ptrdiff_t amount) throw() {
            _position -= amount;
            return *this;
        }

        /**
         * Compute the iterator resulting from advancing the position of `it` by `amount`.
         * Runtime: `O(1)`
         * @param it Iterator to compute advancement for.
         * @param amount Amount to advance by.
         * @return The resulting iterator.
         */
        IteratorBase operator +(const ptrdiff_t amount) const throw() {
            return IteratorBase(*this) += amount;
        }
        
        /**
         * Compute the iterator resulting from advancing the position of `it` by `amount`.
         * Runtime: `O(1)`
         * @param amount Amount to advance by.
         * @param it Iterator to compute advancement for.
         * @return The resulting iterator.
         */
        friend IteratorBase operator +(const ptrdiff_t amount, const IteratorBase& it) throw() {
            return it + amount;            
        }

        /**
         * Compute the iterator resulting from regressing the position of `it` by `amount`.
         * Runtime: `O(1)`
         * @param it Iterator to compute advancement for.
         * @param amount Amount to advance by.
         * @return The resulting iterator.
         */
        IteratorBase operator -(const ptrdiff_t amount) const throw() {
            return IteratorBase(*this) -= amount;
        }

        /**
         * Computes the number of elements between `*this` and `that` assuming they are iterating in the same
         * direction and on the same container.
         * If this is not the case, the returned difference will be the difference between the offsets with respect 
         * to the starting elements of `*this` and `that`.
         * Runtime: `O(1)`
         * @param that Iterator to compute difference for.
         * @return Difference between positional offsets of `*this` and `that`.
         */
        ptrdiff_t operator -(const ConstIterator& that) const throw() {
            return static_cast<ptrdiff_t>(_position) - that._position;
        }
        
        /**
         * Access the element pointed to by `*this`.
         * Runtime: `O(1)`
         * Exception Safety: Strong
         * @return A reference to the value pointed to by `*this`.
         * @throws std::length_error If `*this` is pointing to an out-of-bounds element.
         */
        MemberType& operator *() const {
            return dereferenceAt(_vectorDequePtr, static_cast<ptrdiff_t>(_position));
        }

        /**
         * Access the member of the value pointed to by `*this`.
         * Runtime: `O(1)`
         * @return Member of the value pointed to by `*this`.
         * @throws std::length_error If `*this` is pointing to an out-of-bounds element.
         */
        MemberType* operator ->() const throw() {
            return &(**this);
        }

        /**
         * Access the member resulting from offsetting `*this` by `offset`.
         * Runtime: `O(1)`
         * Exception Safety: Strong
         * @return The member resulting from offsetting `*this` by `offset`.
         * @throws std::length_error If the offset position is out-of-bounds.
         */
        MemberType& operator [](const ptrdiff_t offset) const {
            return dereferenceAt(_vectorDequePtr, static_cast<ptrdiff_t>(_position) + offset);
        }
    };
    
    // Length of current backing array.
    size_t _capacity;

    // The stored data.
    DataType* _data;

    // Index in the backing array of the first element.
    size_t _position;

    // Total number of elements currently contained.
    size_t _size;

    // Add `length` elements from `elements` to the back.
    // Assumes length of internal array has already been verified.
    void _addAll(const DataType* const elements, const size_t start, const size_t length) throw() {
        // Number of elements before wrapping around to beginning.
        const size_t numBeforeWrap = std::min(_capacity - start, length);
        const size_t numAfterWrap = length - numBeforeWrap;
        std::memcpy(_data + start, elements, sizeof(DataType) * numBeforeWrap);
        std::memcpy(_data, elements + numBeforeWrap, sizeof(DataType) * numAfterWrap);
    }
    
    // Check to see if `index` is valid.
    // If not, throw `length_error`.
    void _checkIndex(const size_t index) const {
        if (index >= _size) {
            throw std::length_error(std::to_string(index));
        }
    }

    // Check to see if `it` iterates over `*this`.
    // If not, throw `invalid_argument`.
    template <class IteratorType>
    void _checkIterator(const IteratorType& it) const {
        if (this != it._vectorDequePtr) {
            throw std::invalid_argument("Iterator is not iterating over this VectorDeque");
        }
    }

    // Check to see if `[from, until)` is a valid range.
    // If not, throw `length_error`.
    void _checkRange(const size_t from, const size_t until) const {
        _checkSize(until);
        if (from > until) {
            throw std::invalid_argument("Bad range: start = " + std::to_string(from) + ", end = " + 
                    std::to_string(until));
        }
    }

    // Check to see if this has at least `required` elements.
    // If not, throw `length_error`.
    void _checkSize(const size_t required = 1) const {
        if (required > 0) {
            _checkIndex(required - 1);
        }
    }

    // Check to see if the current backing array has length at least `required`.
    // If not, resize.
    void _ensureCapacity(const size_t required) throw() {
        if (_capacity < required) {
            const size_t newCapacity = required * 2 + 1;
            DataType* const newData = new DataType[newCapacity];
            copyToArray(newData);
            _position = 0;
            delete[] _data;
            _data = newData;
            _capacity = newCapacity;
        }
    }

    // Check to see if `amount` more elements can fit in `*this`.
    // If not, resize.
    void _ensureCanFit(const size_t amount = 1) throw() {
        _ensureCapacity(_size + amount);
    }

    // Initialize the backing array and all fields.
    void _init(const size_t capacity) throw() {
        _capacity = capacity;
        _data = new DataType[capacity];
        _position = 0;
        _size = 0;
    }

    // Optimization: Insert `element` and resize at the same time when _size == _capacity pre-insertion.
    void _insertAndResize(const DataType& element, const size_t before) {
        const size_t newCapacity = 2 * _capacity + 1;
        DataType* const newData = new DataType[newCapacity];
        sliceToArray(newData, 0, before);
        newData[before] = element;
        if (before < _size) {
            // `before == _size` would result in an exception.
            sliceToArray(newData + before + 1, before, _size);
        }
        delete[] _data;
        _data = newData;
        _capacity = newCapacity;
        ++_size;
        _position = 0;
    }

    // Compute the internal index for the offset `offset`.
    size_t _internalIndex(const size_t offset) const throw() {
        if (_position + offset < _capacity) {
            return _position + offset;
        }
        // Target index is past the length of _data: wrap around to the beginning.
        // Note that if `_position + offset == _capacity`, the resulting index is 0.
        return _position + offset - _capacity;
    }

    // Determine the internal index offsetted by `offset` from `from` going backwards.
    size_t _internalNegativeIndexFrom(const size_t from, const size_t offset) const throw() {
        const size_t internal = _internalIndex(from);
        if (internal >= offset) {
            return internal - offset;
        }
        // Target index is before 0: wrap around to the end.
        // Note that if `from == offset - 1`, the resulting index is `_capacity - 1`.
        return _capacity - (offset - internal);
    }

    // Compute the number of elements remaining before we need to wrap to the beginning starting from `start`
    // when `length` elements need to be added.
    size_t _numBeforeWrap(const size_t start, const size_t length) const throw() {
        return std::min(_capacity - start, length);
    }

    // Shift the elements down from `from` until `until`.
    void _shiftDown(const size_t from, const size_t until) throw() {
        // Since elements are overwritten before they are copied, it is safe to use `memcpy`.
        const size_t length = until - from;
        // Start the `memcpy` 1 before the `from`.
        const size_t start = _internalNegativeIndexFrom(from, 1);
        const size_t numBeforeWrap = _numBeforeWrap(start, length);
        const size_t numAfterWrap = length - numBeforeWrap;
        std::memcpy(_data + start, _data + start + 1, sizeof(DataType) * numBeforeWrap);
        if (numAfterWrap != 0) {
            // First internal elements should be "shifted down" to the last position.
            _data[_capacity - 1] = _data[0];
            // Note numAfterWrap >= 1, so this is safe.
            std::memcpy(_data, _data + 1, sizeof(DataType) * (numAfterWrap - 1));
        }
        if (from == 0) {
            // Update the position if we are shifting down the first element.
            if (_position == 0) {
                _position = _capacity - 1;
            } else {
                --_position;
            }
        }
    }

    // Shift the elements up from `from` until `until`.
    void _shiftUp(const size_t from, const size_t until) {
        // Need to start from the end and go backwards, since otherwise elements will be overwritten before they are 
        // copied. Thus, we may not use `memcpy`.
        for (size_t i = 0; i < until - from; ++i) {
            _data[_internalNegativeIndexFrom(until, i)] = _data[_internalNegativeIndexFrom(until, i + 1)];
        }
        if (from == 0) {
            // If we're shifting up the first element, we need to update `_position`.
            if (_position == _capacity - 1) {
                _position = 0;
            } else {
                ++_position;
            }
        }
    }

    // Compute the internal index for where the next element should be written.
    size_t _writePosition() const throw() {
        // We write _size elements after the current position.
        return _internalIndex(_size);
    }      

    public:
    /**
     * Mutable iterator for `VectorDeque`s.
     */
    typedef IteratorBase<VectorDeque, DataType, false> Iterator;

    /**
     * Immutable iterator for `VectorDeque`s.
     */
    typedef IteratorBase<const VectorDeque, const DataType, false> ConstIterator;

    /**
     * Mutable reverse iterator for `VectorDeque`s.
     */
    typedef IteratorBase<VectorDeque, DataType, true> ReverseIterator;

    /**
     * Immutable reverse iterator for `VectorDeque`s.
     */
    typedef IteratorBase<const VectorDeque, const DataType, true> ConstReverseIterator;

    /**
     * The capacity to initialize a `VectorDeque` to by default.
     */
    const static size_t DEFAULT_INITIAL_CAPACITY;

    /**
     * Constructs a `VectorDeque` with a default initial capacity.
     * Runtime: `O(1)`
     */
    VectorDeque() throw() {
        _init(DEFAULT_INITIAL_CAPACITY);
    }

    /**
     * Constructs a `VectorDeque` with the given initial capacity.
     * Runtime: `O(1)`
     * @param capacity Initial capacity to construct with.
     */
    explicit VectorDeque(const size_t capacity) throw() {
        _init(capacity);
    }

    /**
     * Non-temporary copy constructor.
     * Differs from the temporary copy constructor in that the underlying array is copied instead of moved.
     * Runtime: `O(that.size())`
     * @param that `VectorDeque` to construct from.
     */
    VectorDeque(const VectorDeque& that) throw() {
        // Initialize backing array to be large enough to contain the contents of that.
        _init(that._size);
        that.copyToArray(_data);
        // Note that._position is still 0, and we are at capacity.
        _size = that._size;
    }

    /**
     * Temporary copy constructor.
     * Differs from the non-temporary copy constructor in the the underlying array is moved instead of copied.
     * Runtime: `O(1)`
     * @param that Temporary `VectorDeque` to construct from.
     */
    VectorDeque(VectorDeque&& that) throw() {
        // Move contents of that with memcpy.
        std::memcpy(this, &that, sizeof(VectorDeque));
        // Allow safe destruction of that.
        that._data = NULL;
    }

    /**
     * Non-temporary assignment.
     * Differs from temporary assignment in that the underlying array is copied instead of moved.
     * Runtime: `O(that.size())`
     * @param that `VectorDeque` to assign from.
     * @return A reference to `*this`.
     */
    VectorDeque& operator =(const VectorDeque& that) throw() {
        if (this == &that) {
            return *this;
        }
        if (_capacity < that._size) {
            delete[] _data;
            _data = new DataType[that._size];
            _capacity = that._size;
        }
        that.copyToArray(_data);
        _position = 0;
        _size = that._size;
        return *this;
    }

    /**
     * Temporary assignment.
     * Differs from the non-temporary assignment in the the underlying array is moved instead of copied.
     * Runtime: `O(1)`
     * @param that Temporary `VectorDeque` to assign from.
     * @return A reference to `*this`.
     */
    VectorDeque& operator =(VectorDeque&& that) throw() {
        delete[] _data;
        // Move with memcpy.
        std::memcpy(this, &that, sizeof(VectorDeque));
        // Allow safe destruction of that.
        that._data = NULL;
    }

    /**
     * Checks to see if `*this` is equal to another `VectorDeque`.
     * Runtime:` O(size())`
     * @param that Other `VectorDeque` to check equality for.
     * @return true If `(*this)[i] == that[i]` for every `0 <= i < size()` and `this->size() == that.size()`.
     */
    bool operator ==(const VectorDeque& that) const throw() {
        if (this == &that) {
            return true;
        }
        if (_size != that.size()) {
            return false;
        }
        for (size_t i = 0; i < _size; ++i) {
            if ((*this)[i] != that[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Checks to see if `*this` is not equal to another VectorDeque.
     * Runtime: `O(size())`
     * @param that Other `VectorDeque` to check inequality for.
     * @return `true` If `(*this)[i] != that[i]` for some `0 <= i < size()` or `this->size() != that.size()`.
     */
    bool operator !=(const VectorDeque& that) const throw() {
        return !(*this == that);
    }

    /**
     * Access the element at `index`.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @param index Index to get an element at.
     * @return A reference to the element.
     * @throws std::length_error If `index >= size()`.
     */
    DataType& operator [](const size_t index) const {
        _checkIndex(index);
        return _data[_internalIndex(index)];
    }

    /**
     * Gives a human-readable representation of `*this`.
     * Runtime: `O(size())`
     * @return Each element of `*this`, comma-separated and enclosed in curly braces.
     */
    operator std::string() const throw() {
        if (isEmpty()) {
            return "{}";
        }
        std::stringstream stream;
        stream << '{';
        stream << (*this)[0];
        for (size_t i = 1; i < _size; ++i) {
            stream << ", " << (*this)[i];
        }
        stream << '}';
        return stream.str();
    }

    /**
     * Add `element` to the back of `*this`.
     * Runtime: `O(1)`
     * @param element Element to add.
     */
    void add(const DataType& element) throw() {
        _ensureCanFit();
        _data[_writePosition()] = element;
        ++_size;
    }

    /**
     * Add an array of elements to the back of `*this`.
     * Runtime: `O(length)`
     * @param elements Elements to add.
     * @param length Amount of elements to add.
     */
    void addAll(const DataType* const elements, const size_t length) throw() {
        _ensureCanFit(length);
        _addAll(elements, _writePosition(), length);
        _size += length;
    }

    /**
     * Add a collection of elements to the back of `*this`.
     * Runtime: `O(size of given collection)`
     * @param begin Iterator to the first element to add.
     * @param end Iterator past the last element to add.
     * @param IteratorType The type of the iterator.
     */
    template <class IteratorType>
    void addAll(IteratorType begin, IteratorType end) throw() {
        for (IteratorType it = begin; it != end; ++it) {
            add(*it);
        }
    }

    /**
     * Add an array of elements to the front of `*this`.
     * This method works as though `addFirst` was sequentially called on `elements`.
     * Thus, the last element added is the first element in `*this` after `addAllFirst` terminates.
     * Runtime: `O(length)`
     * @param elements Elements to add.
     * @param length Amount of elements to add.
     */
    void addAllFirst(const DataType* const elements, const size_t length) throw() {
        // Can't take advantage of memcpy: use iterator version.
        addAllFirst(elements, elements + length);
    }

    /**
     * Add a collection of elements to the front of `*this`.
     * This method works as though `addFirst` was sequentially called on for the given iterator.
     * Thus, the last element added is the first element in `*this` after `addAllFirst` terminates.
     * Runtime: `O(size of given collection)`
     * @param begin Iterator to the first element to add.
     * @param end Iterator past the last element to add.
     * @param IteratorType The type of the iterator.
     */
    template <class IteratorType>
    void addAllFirst(IteratorType begin, IteratorType end) throw() {
        for (IteratorType it = begin; it != end; ++it) {
            addFirst(*it);
        }
    }

    /**
     * Add `element` to the front of `*this`.
     * Runtime: `O(1)`
     * @param element Element to add.
     */
    void addFirst(const DataType& element) throw() {
        _ensureCanFit();
        if (_position == 0) {
            _position = _capacity - 1;
        } else {
            --_position;
        }
        // The position is now at the element which was added to the front.
        _data[_position] = element;
        ++_size;
    }

    /**
     * Get an iterator pointing to the first element of `*this`.
     * Runtime: `O(1)`
     * @return Iterator pointing to the first element of `*this`.
     */
    Iterator begin() throw() {
        return Iterator(this);
    }

    /**
     * Get a constant iterator pointing to the first element of `*this`.
     * Runtime: `O(1)`
     * @return Constant iterator pointing to the first element of `*this`.
     */
    ConstIterator cbegin() const throw() {
        return ConstIterator(this);
    }

    /**
     * Get an iterator past the last element of `*this`.
     * Runtime: `O(1)`
     * @return Iterator past the last element of `*this`.
     */
    ConstIterator cend() const throw() {
        return ConstIterator(this, _size);
    }

    /**
     * Remove all elements from `*this`.
     * Runtime: `O(1)`.
     */
    void clear() throw() {
        _size = 0;
    }

    /**
     * Check to see if `element` is contained in `*this`.
     * Runtime: `O(size())`
     * @param element Element to check for.
     * @return `true` If `(*this)[i] == element` for some `0 <= i < size()` and `false` otherwise.
     */
    bool contains(const DataType& element) const throw() {
        return find(element) != -1;
    }

    /**
     * Copy the contents of `*this` to `target`.
     * Runtime: `O(size())`
     * @param target Array to copy to.
     */
    void copyToArray(DataType* const target) const throw() {
        sliceToArray(target, 0, _size);
    }

    /**
     * Get a constant reverse iterator pointing to the last element of `*this`.
     * Runtime: `O(1)`
     * @return Constant reverse iterator pointing to the last element of `*this`.
     */
    ConstReverseIterator crbegin() const throw() {
        return ConstReverseIterator(this);
    }

    /**
     * Get an iterator past the last element of `*this`.
     * Runtime: `O(1)`
     * @return Iterator past the last element of `*this`.
     */
    ConstReverseIterator crend() const throw() {
        return ConstReverseIterator(this, _size);
    } 

    /**
     * Get an iterator past the last element of `*this`.
     * Runtime: `O(1)`
     * @return Iterator past the last element of `*this`.
     */
    Iterator end() throw() {
        return Iterator(this, _size);
    }
    
    /**
     * Check to see where `element` is located in `*this`.
     * Runtime: `O(size())`
     * @param element Element to check for.
     * @returns The first `i` such that `(`*this`)[i] == element` or `-1` if no such element exists.
     */
    ssize_t find(const DataType& element) const throw() {
        for (size_t i = 0; i < _size; ++i) {
            if (element == (*this)[i]) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Access the element at `index` starting from the last element.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @param index Index to get an element at.
     * @return A reference to the element.
     * @throws std::length_error If `index >= size()`.
     */
     DataType& fromBack(const size_t index) const {
        return (*this)[_size - index - 1];
    } 

    /**
     * Insert `element` before `before`.
     * Runtime: Amortized `O(min(before, size() - before))`
     * Exception Safety: Strong
     * @param element Element to insert.
     * @param before Index of the element to insert before. The inserted element's index will be `before`.
     * @throws std::length_error If `before > size()`.
     */
    void insert(const DataType& element, const size_t before) {
        if (before == 0) {
            // Handle the logic for 0 specially since it changes the position.
            addFirst(element);
            return;
        }
        if (before != _size) {
            // `before == _size` is okay because it translates to inserting `element` at the end.
            _checkIndex(before);
        } else {
            add(element);
            return;
        }
        if (_size == _capacity) {
            // Handle insertion and resizing simultaneously for efficiency.
            _insertAndResize(element, before);
            return;
        }
    
        if (before <= _size / 2) {
            // More efficient to shift front elements backwards.
            _shiftDown(0, before);

        } else {
            // More efficient to shift back elements forwards.
            _shiftUp(before, _size);
        }
        ++_size;
        const size_t insertionIndex = _internalIndex(before);
        _data[insertionIndex] = element;
    }

    /**
     * Insert `element` before the element pointed to by `it`.
     * If the call is successful, the iterator will be pointing to the new element.
     * Runtime: `O(size())`
     * Exception Safety: Strong
     * @param it Iterator whose pointed-to element will be after the inserted element.
     * @throws std::length_error If `it` points to an out-of-bounds element.
     * @throws std::invalid_argument If `it` is not iterating over `*this`.
     */
    void insert(const DataType& element, const ConstIterator& it) {
        _checkIterator(it);
        insert(element, it._position);
    }

    /**
     * Insert `element` after (with respect to `*this`) the element pointed to by the reverse iterator `it`.
     * If the call is successful, the iterator will be pointing to the new element.
     * Runtime: `O(size())`
     * Exception Safety: Strong
     * @param it Iterator whose pointed-to element will be after the inserted element.
     * @throws std::length_error If `it` points to an out-of-bounds element.
     * @throws std::invalid_argument If `it` is not iterating over `*this`.
     */
    void insert(const DataType& element, const ConstReverseIterator& it) {
        _checkIterator(it);
        insert(element, _size - it._position);
    }

    /**
     * Checks whether `*this` is empty.
     * Runtime: `O(1)`
     * @returns `true` If `size() == 0`, `false` otherwise.
     */
    bool isEmpty() const throw() {
        return _size == 0;
    }

    /**
     * Get the first element of `*this`.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @return The first element of `*this`.
     * @throws std::length_error If `isEmpty()`.
     */
    DataType peek() const {
        _checkSize();
        return (*this)[0];
    }

    /**
     * Get the last element of `*this`.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @return The last element of `*this`.
     * @throws std::length_error If `isEmpty()`.
     */
    DataType peekLast() const {
        _checkSize();
        return (*this)[_size - 1];
    }

    /**
     * Remove and return the first element.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @return The first element.
     * @throws std::length_error If `isEmpty()`.
     */
    DataType pop() {
        _checkSize();
        const DataType popped = peek();
        skip();
        return popped;
    }

    /**
     * Put every element into `target` and then remove them from `*this`.
     * Runtime: `O(size())`
     * @param target Array to put elements into.
     */
    void popAll(DataType* const target) throw() {
        copyToArray(target);
        clear();
    }

    /**
     * Put every element into `target` from the back and then remove them from `*this`.
     * Runtime: `O(size())`
     * @param target Array to put elements into.
     */
    void popAllLast(DataType* const target) throw() {
        reverseCopyToArray(target);
        clear();
    }

    /**
     * Remove and return the last element.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @return The last element.
     * @throws std::length_error If isEmpty().
     */
    DataType popLast() {
        _checkSize();
        const DataType popped = peekLast();
        skipLast();
        return popped;
    }

    /**
     * Remove `amount` elements and put them into `target`.
     * Runtime: `O(amount)`
     * Exception Safety: Strong
     * @param target Array to put removed elements into.
     * @throws std::length_error If `size() < amount`.
     */
    void popSome(DataType* const target, const size_t amount) {
        sliceToArray(target, 0, amount);
        skip(amount);
    }

    /**
     * Remove `amount` elements from the back and put them into `target`.
     * This method works as if `amount` invocations of `popLast` were sequentially called on `*this`.
     * Thus, the last element popped will be the last element in `target`.
     * Runtime: `O(amount)`
     * Exception Safety: Strong
     * @param target Array to put removed elements into.
     * @throws std::length_error If `size() < amount`.
     */
    void popSomeLast(DataType* const target, const size_t amount) {
        reverseSliceToArray(target, 0, amount);
        skipLast(amount);
    }

    /**
     * Get a reverse iterator pointing to the last element of `*this`.
     * Runtime: `O(1)`
     * @return Reverse iterator pointing to the first element of `*this`.
     */
    ReverseIterator rbegin() throw() {
        return ReverseIterator(this);
    }

    /**
     * Remove the element at `index`.
     * Runtime: `O(size())`
     * Exception Safety: Strong
     * @param index Index to remove the element at.
     * @return The removed element.
     * @throws std::length_error If `index >= size()`.
     */
    DataType removeAt(const size_t index) {
        _checkIndex(index);
        const DataType result = (*this)[index];
        if (index == _size - 1) {
            --_size;
        }
        else if (index / 2 <= _size) {
            // More efficient to shift front elements forward.
            _shiftUp(0, index);
            --_size;

        } else {
            // More efficient to shift back elements backward.
            _shiftDown(index + 1, _size);
            --_size;
        }
        return result;
    }
    
    /**
     * Remove the element pointed to by `it`.
     * Runtime: `O(size())`
     * Exception Safety: Strong
     * @param it Iterator to remove the pointed-to element for.
     * @return The removed element.
     * @throws std::length_error If `it` points to an out-of-bounds element.
     * @throws std::invalid_argument If `it` is not iterating over `*this`.
     */
    DataType removeAt(const ConstIterator& it) {
        _checkIterator(it);
        return removeAt(it._position);
    }

    /**
     * Remove the element pointed to by `it`.
     * Runtime: `O(size())`
     * Exception Safety: Strong
     * @param it Iterator to remove the pointed-to element for.
     * @return The removed element.
     * @throws std::length_error If `it` points to an out-of-bounds element.
     * @throws std::invalid_argument If `it` is not iterating over `*this`.
     */
    DataType removeAt(const ConstReverseIterator& it) {
        _checkIterator(it);
        removeAt(_size - it._position);
    }

    /**
     * Get an iterator past the last element of `*this`.
     * Runtime: `O(1)`
     * @return Iterator past the last element of `*this`.
     */
    Iterator rend() throw() {
        return ReverseIterator(this, _size);
    } 

    /**
     * Copy the contents of `*this` to the given array in reverse order.
     * Runtime: `O(size())`
     * @param target Array to copy to.
     */
    void reverseCopyToArray(DataType* const target) const throw() {
        reverseSliceToArray(target, 0, _size);
    }

    /**
     * Copy a slice of contents of `*this` to `target` in reverse order.
     * Runtime: `O(until - from)`
     * Exception Safety: Strong
     * @param target Array to copy to.
     * @param from Index of `*this` to start copying.
     * @param until Index of `*this` to stop copying (exclusive).
     * @throws std::length_error If `until > size()`.
     * @throws std::invalid_argument If `from > until`.
     */
    void reverseSliceToArray(DataType* const target, const size_t from, const size_t until) const {
        _checkRange(from, until);
        const size_t length = until - from;
        for (size_t i = 0; i < length; ++i) {
            target[i] = fromBack(i + from);
        }
    }

    /**
     * Returns the number of elements in `*this`.
     * Runtime: `O(1)`
     * @return The number of elements in `*this`.
     */
    size_t size() const throw() {
        return _size;
    }

    /**
     * Removes `amount` elements from the front of `*this`.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @param amount Amount of elements to remove.
     * @throws std::length_error If `amount > size()`.
     */
    void skip(const size_t amount = 1) {
        _checkSize(amount);
        _position = _internalIndex(amount);
        _size -= amount;
    }

    /**
     * Removes `amount` elements from the back of `*this`.
     * Runtime: `O(1)`
     * Exception Safety: Strong
     * @param amount Amount of elements to remove.
     * @throws std::length_error If `amount > size()`
     */
    void skipLast(const size_t amount = 1) {
        _checkSize(amount);
        // _position is already fine, since we are not removing from the front.
        _size -= amount;
    }

    /**
     * Copy a slice of elements of `*this` to `target`.
     * Runtime: `O(until - from)`
     * Exception Safety: Strong
     * @param target Array to copy to.
     * @param from Index of `*this` to start copying.
     * @param until Index of `*this` to stop copying (exclusive).
     * @throws std::length_error If `until > size()` or `from > until`.
     */
    void sliceToArray(DataType* const target, const size_t from, const size_t until) const {
        _checkRange(from, until);
        const size_t length = until - from;
        const size_t start = _internalIndex(from);
        const size_t numBeforeWrap = _numBeforeWrap(start, length);
        const size_t numAfterWrap = length - numBeforeWrap;
        memcpy(target, _data + start, sizeof(DataType) * numBeforeWrap);
        memcpy(target + numBeforeWrap, _data, sizeof(DataType) *  numAfterWrap);
    }
};

template <class DataType>
const size_t VectorDeque<DataType>::DEFAULT_INITIAL_CAPACITY = 11;

// Leftover friend function.

template <class DataType, class VectorDequeType, class MemberType, bool IS_REVERSE>
typename VectorDeque<DataType>::template IteratorBase<VectorDequeType, MemberType, IS_REVERSE> operator +
    (const ptrdiff_t amount, const typename VectorDeque<DataType>::template 
    IteratorBase<VectorDequeType, MemberType, IS_REVERSE>& it) throw();