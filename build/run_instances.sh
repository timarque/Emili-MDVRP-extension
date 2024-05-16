#!/bin/bash

PROGRAM="./emili"
INSTANCES_DIR="/home/tagotuga/Emili-MDVRP-extension/instances"
cleanup() {
    echo "Stopping script execution..."
    exit 1
}

trap cleanup SIGINT

for file_path in "$INSTANCES_DIR"/*; do
    instance_name=$(basename "$file_path")
    echo "Processing file: $file_path"
    $PROGRAM "$file_path" "MDVRP" "fils" "vnd" "first" "cw" "locmin" "2opt" "2opt*" "exchange" "move" "exchange2" "iteration" "rndmv" "exchange" "10" "test" "100" "-it" "1200" "rnds" "9" 
done
