# cpp-result
An alternative implementation for std::optional with more features. You can just download the header file and include it in your project.

## Quick Documentation
The `opt::result<T>` class can contain either a value of type `T` or an error. An error instance signals not only the absence of a value, but also the reason for the error if one exists. To create a result you need to use `of()` or `empty()`. For example, `opt::of(10)` will create an integer result which carries the value of 10. On the other hand, `opt::empty("invalid integer operation")` creates an empty result with the specified error message.

### Consuming a Value and Handling Errors
In order to consume a value (do an operation on it without returning another value) you can use `if_defined()` which takes a void function or a lambda expression that takes a `const T &` argument. The opposite of `if_defined()` is `if_empty()` which also takes a function that takes a `const opt::error &` argument. You can chain the two like `result.if_defined(consume).if_empty(print)`.

### Mapping a Value
Another useful operation which could be done is mapping. You can a map the value, if present, to another value. It doesn't matter if the mapping function returns an instance of `opt::result` or just a normal value as both of them will lead to the same result. Mapping is particulary useful for chaining multiple operations together with a single error handling function.
