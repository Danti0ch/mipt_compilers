project(Visitor)
set(
    HEADERS
    driver.hh
    parser.hh
    )

find_package(BISON)
find_package(FLEX)

BISON_TARGET(
    ParserVisitor
    parser.y
    ${Visitor_SOURCE_DIR}/parser.cpp
    COMPILE_FLAGS --graph
    DEFINES_FILE ${Visitor_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    ScannerVisitor
    scanner.l
    ${Visitor_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(ScannerVisitor ParserVisitor)

add_executable(
    VisitorExecutable
    main.cpp
    driver.cpp
    ${BISON_ParserVisitor_OUTPUTS}
    ${FLEX_ScannerVisitor_OUTPUTS}
    nterms/Statement.cpp
    visitors/Interpreter.cpp
    visitors/PrintVisitor.cpp
)

target_include_directories(
    VisitorExecutable PRIVATE ${Visitor_SOURCE_DIR}
)

add_custom_target(
    VisitorTree
    COMMAND dot -Tpng ${Visitor_SOURCE_DIR}/parser.gv -o ${Visitor_SOURCE_DIR}/parser.png
    
    DEPENDS ${Visitor_SOURCE_DIR}/parser.cpp
)

add_dependencies(VisitorExecutable VisitorTree)
