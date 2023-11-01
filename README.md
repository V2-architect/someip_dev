# someip_dev
SOME/IP Service Development Environment

[dependencies]
- required library: [boost, vsomeip3, commonapi-core, commonapi-someip]

[dependency directory structure]
${ROOT_PATH}
`-- ${LIB_NAME}_{VERSION}
    |-- include
    `-- lib

example)
${ROOT_PATH}
|-- boost_1_64_0
|   |-- include
|   `-- lib
|-- capicxx-core-runtime_3.2.0
|   |-- include
|   `-- lib
|-- capicxx-someip-runtime_3.2.0
|   |-- include
|   `-- lib
`-- vsomeip_3.3.0
    |-- include
    `-- lib

[SOME/IP service]
- need to read 'services/README.txt'


