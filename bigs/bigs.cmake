# Este fichero es para su inclusión desde proyectos externos
#
# En CMakeLists.txt del nuevo proyecto se debe poner:
#  include(<path>/bigs.cmake)
#  indicando la ruta completa (relativa o absoluta) al directorio en donde está BiGS

# Obtener PATH absoluto 
get_filename_component(BIGS_DIR_ABS ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)

set(BIGS_LIB ${BIGS_DIR_ABS}/lib)
set(BIGS_IMPLIB ${BIGS_DIR_ABS}/lib/libbigs.a)
set(BIGS_INC ${BIGS_DIR_ABS}/include)
set(BIGS_LOCATION ${BIGS_DIR_ABS}/lib/libbigs.a)

# Localizar biblioteca Allegro
find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_main-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)

# Añadir biblioteca BiGS
add_library(bigs STATIC IMPORTED)

set_target_properties(bigs PROPERTIES 
    IMPORTED_IMPLIB "${BIGS_IMPLIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${BIGS_INC}"
    IMPORTED_LOCATION "${BIGS_LOCATION}"
)

include_directories(${BIGS_INC})
link_directories(${BIGS_LIB})

# Añadir dependencia para que al incluir BiGS se incluya también Allegro
target_link_libraries(bigs INTERFACE ${ALLEGRO_LIBRARIES})
