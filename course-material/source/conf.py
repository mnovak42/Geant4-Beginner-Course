# ==============================================================================
# author: M. Novak
# date  : April 2022
# file  : `conf.py`
#
# Configuration file for the Sphinx documentation builder of the Geant4 Beginner
# Course material: `reStructuredText` and `Doxygen` code documentation connected
# by `breathe` and generated into a single document by `Sphinx`.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html
# ==============================================================================

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
import subprocess

#sys.path.insert(0, os.path.abspath('.'))
sys.path.append(os.path.abspath('.'))
sys.path.append(os.path.abspath('../../applications'))
sys.path.append(os.path.abspath('_extensions'))

# call doxygen to generate the XML files of the C++ code documentation
subprocess.call('cd ..; doxygen Doxyfile.in', shell=True)


# -- Project information -----------------------------------------------------

project = 'Geant4 Beginner Course'
copyright = '2022, M.Novak'
author = 'Mihaly Novak'

# The full version, including alpha/beta/rc tags
#release = '0.0.1'
version = '0.0.1 (Geant4-11.00)'
#release = version


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',    # autogenerate documentation i.e. the .rst files
    'sphinx.ext.doctest',
    'sphinx.ext.intersphinx',
    'sphinx.ext.todo',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',    # to have the [source] option in the doc
    'nbsphinx',               # for jupiter notebook conversions
    'sphinx.ext.napoleon',    # for the google-style doc
    'breathe',                # mixed doxygen and sphinx doc with breathe
    'sphinxcontrib.bibtex',   # to use bibtex
#    'sphinxemoji.sphinxemoji',# fucking emoji
    'geant4extensions',       # our local (_extensions/geant4extensions.py)
]

# set path to the doxygen-generated XML for breathe
breathe_projects = { 'Geant4 Beginner Course': '../doxygen/xml' }


numfig = True
source_suffix = '.rst'
master_doc = 'index'

# consistent sphix emoji style
#sphinxemoji_style = 'twemoji'

# option for autodoc
autodoc_member_order = 'bysource'  # default is alphabetical

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['global.rst']

# Set color style for code highlighting "default"
# (see https://stylishthemes.github.io/Syntax-Themes/pygments/ for more pre-defined styles)
# pygments_style = "default" #"native"

# Possibility of adding global costum role-s
rst_prolog = open('global.rst', 'r').read()

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'
#html_theme = 'alabaster'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
# The css location is relative to `html_static_path` and first I load the
# complete (RTD) `theme.ccs` then modify some components.
# I modify the background of the code highlighting to be dark in the html output.
# But I also added the complete `native` `pygments_style` as a .css so it can be
# use as well to produce the corresponding code highlighted html.
# (The original, lighter background code highlighting stays for the latex output)
html_static_path = ['_static']
def setup(app):
   app.add_css_file("style.css")
   app.add_css_file("css/pygments_native.css")

html_logo = "g4logo-web.png"
html_show_sourcelink = False
#html_show_copyright = False
#html_show_sphinx = False
html_theme_options = {
#    'logo_only': True,
    'display_version': True,
    'navigation_depth': 3,
}


# -- Options for LaTeX output ---------------------------------------------#

latex_elements = {
 # 'papersize': 'a4paper',
# 'releasename':"version: 0.0.1 (\texttt{Geant4-11.00})",
#
# remove white pages
# 'extraclassoptions': 'openany,oneside',
 #
  "preamble": r"""
    \usepackage{amsmath}
    \usepackage{amsfonts}
    \usepackage{amssymb}
    \usepackage{bm}
    \usepackage{bbm}
    \usepackage{booktabs}
%    \usepackage[table,xcdraw]{xcolor}
    \usepackage{rotating,tabularx}
    \usepackage{multirow}
  """,
 'preamble': '\\addto\\captionsenglish{\\renewcommand{\\contentsname}{Table of contents}}',
#  'fncychap': '\\usepackage[Conny]{fncychap}',
#    \usepackage{mathtools}
  'maketitle': r'''
     \pagenumbering{Roman} %%% to avoid page 1 conflict with actual page 1
     \begin{titlepage}
       %% * give space from top
       \vspace*{30mm}
       \textbf{\Huge {\texttt{Geant4} Beginner Course Material}}
       \rule{1.0\linewidth}{2.4pt}\\[-3.7ex] \rule{1.0\linewidth}{0.6pt}
       %% add logo
          \vspace*{20mm}
          \begin{figure}[!h]
             \centering
             \includegraphics[scale=1.1]{g4logo-web.png}
          \end{figure}
       %% add some space
       %% add space till the bottom
       \vfill
       \vspace*{-50mm}
       \centering
       \Large  {\textbf{Mih{\'a}ly Nov{\'a}k}\\ CERN EP-SFT\\}
       \small  {version: 0.0.1 (\texttt{Geant4-11.00})\\}
       \vspace*{35mm}
       \small \textbf{\today}
    \end{titlepage}
    \pagenumbering{arabic}
''',
}

latex_logo = "g4logo-web.png"
## fore latex to have section as the highest level (not chapter or part)
## latex_toplevel_sectioning = 'chapter'

latex_documents = [
    (master_doc, 'geant4beginnercourse.tex', u'G4 doc',
     u'Mihaly Novak', 'howto'),
]
