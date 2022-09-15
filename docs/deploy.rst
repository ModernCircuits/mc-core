Deploy
======

New Version
-----------

- Todo

Conan
-----

.. code-block:: shell

    conan remote add "modern-circuits" https://moderncircuits.jfrog.io/artifactory/api/conan/modern-circuits-conan
    conan user -p $CONAN_PASSWORD -r "modern-circuits" $CONAN_USER

.. code-block:: shell

    export VERSION="0.x.x"
    conan create . modern-circuits/stable -pr default -s compiler.cppstd=17 -c user.build:all=True -b outdated -u -s build_type=Release
    conan upload mc-core/$VERSION@modern-circuits/stable -r modern-circuits --all
