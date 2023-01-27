FIRST_NAME := "Jack"
LAST_NAME := "Morrison"
SUBMISSION_DIR := justfile_directory() / "submissions"

# list the available commands
list:
    just --list

# run the specified c file by first compiling it with gcc
run buildfile *args:
    #!/usr/bin/env bash

    set -euo pipefail

    mkdir -p "{{justfile_directory()}}/target"
    OUTNAME=$(basename {{buildfile}} .c)
    gcc -o "{{justfile_directory()}}/target/${OUTNAME}" "{{buildfile}}" -lm
    sh -c "{{justfile_directory()}}/target/${OUTNAME}" {{args}}

# zip up the lab folder
zip labdir:
    #!/usr/bin/env bash
    
    set -euo pipefail

    mkdir -p "{{SUBMISSION_DIR}}/{{labdir}}"
    rm -f "{{SUBMISSION_DIR}}/{{labdir}}/{{labdir}}.zip"
    zip -r "{{SUBMISSION_DIR}}/{{labdir}}/{{labdir}}.zip" "{{labdir}}"

write labdir:
    #!/usr/bin/env bash

    set -euo pipefail

    mkdir -p "{{SUBMISSION_DIR}}/{{labdir}}"
    sh -c "{{justfile_directory()}}/docwriter/venv/bin/python {{justfile_directory()}}/docwriter/main.py {{SUBMISSION_DIR}}/{{labdir}}/{{labdir}}.pdf {{labdir}}"

prepare labdir:
    #!/usr/bin/env bash

    set -euo pipefail
    just zip {{labdir}}
    just write {{labdir}}
