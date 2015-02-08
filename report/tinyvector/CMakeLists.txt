cmake_minimum_required(VERSION 2.8)

include(UseLatex.cmake)

add_latex_document(optimization.tex 
    #BIBFILES ldynbib.bib 
    IMAGE_DIRS results
    #USE_INDEX
    DEFAULT_PDF)
