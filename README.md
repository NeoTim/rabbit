Rabbit
======
Rabbit is a header-only C++ API of Raspberry Pi.

Usage
-----
Just include needed headers in the `Rabbit` directory.  The identifiers are
wrapped in the `Rabbit` namespace to prevent collision.

### Rabbit::AutoCloseable ###
Automatic resource handler like `AutoCloseable` in Java.  This class helps
properly `close` Un\*x file descriptors.

### Rabbit::GPIO ###
Wrapped access to memory-mapped `/dev/gpiomem`.

License
-------
This library is licensed in GPLv3+.
