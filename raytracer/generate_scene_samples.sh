#!/bin/sh

# Script to generate images for a specific scene with varying sample counts.
# Usage: ./generate_scene_samples.sh <scene_name>

# Exit immediately if a command exits with a non-zero status.
set -e

# --- Configuration ---
SRC_DIR="examples"
BUILD_DIR="build"
OUTPUT_DIR="output"
SAMPLES="1 5 25 100"
CXX="g++"
CXXFLAGS="-std=c++11 -O3"
INC_DIR="-I."
# --- End Configuration ---

# Check if scene name is provided
if [ -z "$1" ]; then
  echo "Usage: $0 <scene_name>"
  exit 1
fi

SCENE_NAME=$1
SCENE_FILE="$SRC_DIR/${SCENE_NAME}.cpp"

# Determine the base output PPM filename expected from the C++ code
BASE_PPM_NAME=""
if [ "$SCENE_NAME" = "cornell_box" ]; then
    BASE_PPM_NAME="cornell_box_reference.ppm"
elif [ "$SCENE_NAME" = "rectangular_light_scene" ]; then
    BASE_PPM_NAME="rectangular_light_scene.ppm"
elif [ "$SCENE_NAME" = "reflective_floor" ]; then
    BASE_PPM_NAME="reflective_floor_scene.ppm"
else
    echo "Error: Unknown base PPM name for scene '$SCENE_NAME'"
    exit 1
fi

echo "Processing scene: $SCENE_NAME (Source: $SCENE_FILE, Base Output: $BASE_PPM_NAME)"

# Check if source file exists
if [ ! -f "$SCENE_FILE" ]; then
    echo "Error: Source file not found: $SCENE_FILE"
    exit 1
fi

# Backup original file
echo "Backing up $SCENE_FILE to $SCENE_FILE.bak..."
cp "$SCENE_FILE" "$SCENE_FILE.bak"

# Ensure build directory exists
mkdir -p "$BUILD_DIR"

# Loop through sample counts
for SAMPLE_COUNT in $SAMPLES; do
    echo "  Samples: $SAMPLE_COUNT"
    SAMPLE_DIR="$OUTPUT_DIR/$SCENE_NAME/${SAMPLE_COUNT}_samples"
    mkdir -p "$SAMPLE_DIR"

    echo "    Modifying $SCENE_FILE for $SAMPLE_COUNT samples..."
    # Modify samplesPerPixel using sed (use specific pattern)
    # Using | as delimiter to avoid issues if paths contain /
    sed -i.sedbak "s|int samplesPerPixel = [0-9][0-9]*;|int samplesPerPixel = ${SAMPLE_COUNT};|" "$SCENE_FILE"

    # Check if sed succeeded
    if cmp -s "$SCENE_FILE" "$SCENE_FILE.bak"; then
        echo "    WARNING: sed command might not have modified $SCENE_FILE. Check the 'samplesPerPixel' line."
    fi
    rm -f "$SCENE_FILE.sedbak" # Clean up sed backup

    EXECUTABLE_NAME="$BUILD_DIR/${SCENE_NAME}_${SAMPLE_COUNT}samples"
    echo "    Compiling to $EXECUTABLE_NAME..."
    $CXX $CXXFLAGS $INC_DIR "$SCENE_FILE" -o "$EXECUTABLE_NAME"

    echo "    Executing $EXECUTABLE_NAME..."
    # Ensure the expected output file doesn't exist in build dir
    rm -f "$BUILD_DIR/$BASE_PPM_NAME"
    # Execute in a subshell to handle cd
    (cd "$BUILD_DIR" && "./${SCENE_NAME}_${SAMPLE_COUNT}samples")

    OUTPUT_PPM="$SAMPLE_DIR/${SCENE_NAME}_${SAMPLE_COUNT}samples.ppm"
    BUILD_PPM_PATH="$BUILD_DIR/$BASE_PPM_NAME"

    # Check if PPM file was created in build dir and move it
    if [ -f "$BUILD_PPM_PATH" ]; then
        echo "    Moving $BUILD_PPM_PATH to $OUTPUT_PPM..."
        mv "$BUILD_PPM_PATH" "$OUTPUT_PPM"

        # Optional PNG conversion
        if command -v convert >/dev/null 2>&1; then
            OUTPUT_PNG="$SAMPLE_DIR/${SCENE_NAME}_${SAMPLE_COUNT}samples.png"
            echo "    Converting $OUTPUT_PPM to $OUTPUT_PNG..."
            convert "$OUTPUT_PPM" "$OUTPUT_PNG"
        else
            echo "    ImageMagick not found. PNG not generated."
        fi
    else
        echo "    ERROR: Expected output file $BUILD_PPM_PATH not found after execution."
        # Decide whether to continue or exit. For now, continue.
    fi

    # Clean up executable
    rm -f "$EXECUTABLE_NAME"
done

# Restore original file
echo "Restoring original $SCENE_FILE from $SCENE_FILE.bak..."
mv "$SCENE_FILE.bak" "$SCENE_FILE"

echo "Processing for scene $SCENE_NAME completed."

exit 0 