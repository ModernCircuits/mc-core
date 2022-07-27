Deploy
======

New Version
-----------

- Todo

Conan
-----

.. code-block:: shell

    export CONAN_REMOTE="modern-circuits"
    conan remote add $CONAN_REMOTE https://moderncircuits.jfrog.io/artifactory/api/conan/modern-circuits-conan
    conan user -p $CONAN_PASSWORD -r $CONAN_REMOTE $CONAN_USER

.. code-block:: shell

    export VERSION="0.2.0"
    export CXXSTD=20
    export CHANNEL="modern-circuits/stable"
    export BUILD_TYPE=Release

    conan create . $CHANNEL -pr default -s compiler.cppstd=$CXXSTD -e mc-core:CONAN_RUN_TESTS=True -b outdated -u -s build_type=$BUILD_TYPE
    conan upload mc-core/$VERSION@$CHANNEL -r $CONAN_REMOTE --all
