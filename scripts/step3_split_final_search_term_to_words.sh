#!/bin/bash
# split_to_words.sh
# Usage: ./split_to_words.sh input.txt output.txt
# Creates:
#   - OUTPUT               → all normalized words
#   - W2CNT_OUTPUT         → word counts
#   - SORTED_UNIQ_OUTPUT   → filtered, sorted words (count >= 5)

INPUT="$1"
OUTPUT="$2"
W2CNT_OUTPUT="w2cnt_$OUTPUT"
SORTED_W2CNT_OUTPUT="sorted_w2cnt_$OUTPUT"
FILTERED_OUTPUT="filtered_$OUTPUT"

if [ -z "$INPUT" ] || [ -z "$OUTPUT" ]; then
  echo "Usage: $0 input.txt output.txt"
  exit 1
fi

# Step 1: Normalize and tokenize
LC_ALL=C tr -cs '[:alnum:]' '\n' < "$INPUT" \
  | tr '[:upper:]' '[:lower:]' \
  | grep -v '^$' > "$OUTPUT"

echo "✅ Wrote tokenized words from $INPUT → $OUTPUT"

# Step 2: Count word frequencies
awk '{count[$0]++} END {for (w in count) print w "\t" count[w]}' "$OUTPUT" > "$W2CNT_OUTPUT"

# Step 3: sort descending
sort -k2,2nr "$W2CNT_OUTPUT" > "$SORTED_W2CNT_OUTPUT"

# Step 4: Filter sorted words with count >= 5
awk -F'\t' '$2 >= 5 {print $1}' "$SORTED_W2CNT_OUTPUT" > "$FILTERED_OUTPUT"

echo "✅ Word counts written to $W2CNT_OUTPUT"
echo "✅ Filtered & sorted words (count ≥ 5) written to $SORTED_W2CNT_OUTPUT and $FILTERED_OUTPUT"
