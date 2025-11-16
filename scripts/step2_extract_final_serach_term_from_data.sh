#!/bin/bash
# extract_final_search_term.sh
# Usage: ./extract_final_search_term.sh /path/to/folder output.tsv

FOLDER="$1"
OUTPUT="$2"

if [ -z "$FOLDER" ] || [ -z "$OUTPUT" ]; then
  echo "Usage: $0 folder output.tsv"
  exit 1
fi

# header
echo "final_search_term" > "$OUTPUT"

for file in "$FOLDER"/*.parquet; do
  echo "Processing $file ..."
  parquet-tools cat "$file" \
    | jq -r '.[] | .final_search_term // empty' >> "$OUTPUT"
done

echo "✅ Extracted final_search_term from all Parquet files in $FOLDER → $OUTPUT"

