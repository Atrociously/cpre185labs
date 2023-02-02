FIRST_NAME := "Jack"
LAST_NAME := "Morrison"
SUBMISSION_DIR := justfile_directory() / "submissions"
PY := justfile_directory() / "docwriter/venv/bin/python"
PY_MAIN := justfile_directory() / "docwriter/main.py"

# list the available commands
list:
    just --list

# start a new lab
start daynum:
    #!/usr/bin/env bash
    set -euo pipefail

    NEWDIR="{{justfile_directory()}}/lab{{daynum}}"
    mkdir -p "${NEWDIR}"
    cp "{{justfile_directory()}}/lab_report_template.odt" "$NEWDIR/lab{{daynum}}_report.odt"

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

    OUTPUT="{{SUBMISSION_DIR}}/{{labdir}}/{{FIRST_NAME}}_{{LAST_NAME}}_{{labdir}}.zip"
    mkdir -p "{{SUBMISSION_DIR}}/{{labdir}}"
    rm -f "${OUTPUT}"
    zip -r "${OUTPUT}" "{{labdir}}"

write labdir:
    #!/usr/bin/env bash
    set -euo pipefail

    OUTPUT="{{SUBMISSION_DIR}}/{{labdir}}/{{FIRST_NAME}}_{{LAST_NAME}}_{{labdir}}.docx"

    mkdir -p "{{SUBMISSION_DIR}}/{{labdir}}"
    sh -c "{{PY}} {{PY_MAIN}} ${OUTPUT} {{labdir}}"

prepare labdir:
    #!/usr/bin/env bash

    set -euo pipefail
    just zip {{labdir}}
    just write {{labdir}}
