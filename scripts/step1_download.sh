#!/bin/bash
DATASET="amazon/AmazonQAC"
SPLIT="train"
OUT_DIR="amazonqac_train"

mkdir -p "$OUT_DIR"

# Fetch file list and download each
curl -s "https://huggingface.co/api/datasets/$DATASET/tree/main/$SPLIT" \
| jq -r '.[].path' \
| while read f; do
    echo "Downloading $f..."
    curl -L -o "$OUT_DIR/$(basename $f)" \
      "https://huggingface.co/datasets/$DATASET/resolve/main/$f"
  done

echo "✅ All files downloaded to $OUT_DIR/"

