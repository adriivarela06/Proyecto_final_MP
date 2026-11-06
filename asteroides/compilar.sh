#!/bin/bash
# Crea la carpeta build si no existe, configura y compila en un solo paso
cmake -B build && cmake --build build
