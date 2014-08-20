#!/bin/bash
/opt/alps/bin/parameter2xml -f trun1;
/opt/alps/bin/spinmc trun1.in.xml
/opt/alps/bin/extracttext ../complot_e.xml trun.out.xml
