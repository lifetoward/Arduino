# source me to shortcut Arduino software work

export ArduinoHome="$HOME/Opera/Arduino" ArduinoBase="$HOME/Library/Arduino"

type -t ardcli || {
    ardcli() {
        "${ArduinoBase}/arduino-cli" --config-file "${ArduinoHome}/arduino-cli.yaml" "$@"
    }
}

type -t ardident || {
    ardident() {
        ensure jq --version &>/dev/null
        local s=$(
            ardcli --format json board list |  
            jq -j '.[]?|select(.boards)|"ArduinoPort=\"",.address,"\" ArduinoBoard=\"",.boards[]?.FQBN,"\""'
        )
        [ -z "$s" ] && {
            echo "No boards found."
            return 1
        }
        echo "Board discovered and set: $s" >&2
        eval export $s
    }
}

type -t ardcompile || {
    ardcompile() {
        [ -z "${ArduinoBoard}" ] && { 
            ardident || {
                echo "Set or discover the FQBN specifier for your target MCU as \$ArduinoBoard."
                echo "(We tried with ardident but it didn't work.)"
                return 1
            }
        }
        ArduinoSketch="${1:-$ArduinoSketch}"
        [ -n "${ArduinoSketch}" ] || {
            echo "Please specify a subject sketch directory"
            return 1
        }
        ardcli compile --fqbn "$ArduinoBoard" "${ArduinoSketch}"
        echo -e "\nCompilation complete for ${ArduinoSketch}."
    }
}

type -t ardpush || {
    ardpush() {
        [ -z "${ArduinoBoard}" -o -z "${ArduinoPort}" ] && {
            ardident || {
                echo "Set or discover the FQBN (\$ArduinoBoard) and Serial Port (\$ArduinoPort) for your target MCU."
                echo '(We tried with `ardident` but it didn''t work.)'
                return 1
            }
        }
        ArduinoSketch="${1:-$ArduinoSketch}"
        [ -n "${ArduinoSketch}" ] || {
            echo "Please specify a subject sketch directory"
            return 1
        }
        ardcli upload --fqbn "$ArduinoBoard" -p "$ArduinoPort" "${ArduinoSketch}"
        echo -e "\nUpload to ${ArduinoBoard} on ${ArduinoPort} complete for ${ArduinoSketch}."
    }
}

type -t ardupdate || {
    ardupdate() {
        ArduinoSketch="${1:-$ArduinoSketch}"
        [ -n "${ArduinoSketch}" ] || {
            echo "Please specify a subject sketch directory"
            return 1
        }
        ardcompile && ardpush
    }
}
