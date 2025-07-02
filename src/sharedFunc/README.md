# Shared Function Access in Libraries

## How Can a Library Access App Functions?

This is a quick test to see how a shared library can access functions defined in the main application using `dlsym`.

### Key Points

- To access app functions from a library, you need to compile your main app with the `-rdynamic` flag. This makes the functions available for the library to find.

- You can also just pass a function pointer to the library, but it is less fun.