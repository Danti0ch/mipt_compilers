project(ParserExampleWithAst)
set(
    HEADERS
    driver.hh
    parser.hh
    )
find_package(BISON)
find_package(FLEX)

BISON_TARGET(
    MyParserWithAst
    parser.y
    ${ParserExampleWithAst_SOURCE_DIR}/parser.cpp
    DEFINES_FILE ${ParserExampleWithAst_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
    MyScannerWithAst
    scanner.l
    ${ParserExampleWithAst_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScannerWithAst MyParserWithAst)

add_executable(
    ParserExampleWithAst
    main.cpp
    driver.cpp
    ${BISON_MyParserWithAst_OUTPUTS}
    ${FLEX_MyScannerWithAst_OUTPUTS}
    nterms/Statement.cpp
)

target_include_directories(
    ParserExampleWithAst PRIVATE ${ParserExampleWithAst_SOURCE_DIR}
)
