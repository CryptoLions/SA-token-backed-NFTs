project(backtoken)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( backtoken backtoken backtoken.cpp )
target_include_directories( backtoken PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( backtoken ${CMAKE_SOURCE_DIR}/../ricardian )