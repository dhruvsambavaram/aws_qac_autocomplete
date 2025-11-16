# AWS QAC Autocomplete — Scripts

This directory contains Bash scripts that automate the end-to-end preprocessing pipeline for the **Amazon QAC dataset**, preparing it for autocomplete or query-expansion modeling.

---

## 📂 Overview of Scripts

### 1️⃣ `step1_download.sh`
**Purpose:**  
Downloads all dataset splits (e.g., `train`, `validation`, etc.) from the **Hugging Face Hub** for the dataset `amazon/AmazonQAC`.

**How it works:**  
- Uses `curl` to query the Hugging Face API and list all files in a dataset split.  
- Iterates through each file path, downloading it into a specified directory (`OUT_DIR`).  
- Creates the directory automatically if missing.

**Example usage:**
```bash
./step1_download.sh
```
This will download all files under `amazon/AmazonQAC/train` into a local folder `amazonqac_train`.

---

### 2️⃣ `step2_extract_final_serach_term_from_data.sh`
**Purpose:**  
Extracts the field `final_search_term` from all `.parquet` files in a given folder and writes them into a single TSV file.

**How it works:**  
- Iterates through all `.parquet` files in a given folder.  
- Uses `parquet-tools cat` combined with `jq` to extract the `final_search_term` field from each row.  
- Outputs all results (one per line) to a TSV file with a header.

**Example usage:**
```bash
./step2_extract_final_serach_term_from_data.sh amazonqac_train final_terms.tsv
```

**Output:**  
`final_terms.tsv` containing:
```
final_search_term
iphone case
wireless charger
...
```

---

### 3️⃣ `step3_split_final_search_term_to_words.sh`
**Purpose:**  
Tokenizes the extracted search terms into individual words and computes word frequency statistics.

**How it works:**
1. Normalizes text to lowercase and splits on non-alphanumeric characters.
2. Writes all words to an output file.
3. Counts word frequencies via `awk`.
4. Sorts them by frequency (descending).
5. Filters to include only words with `count ≥ 5`.

**Generated files:**
- `w2cnt_<output>` → word → count mapping  
- `sorted_w2cnt_<output>` → word counts sorted descending  
- `filtered_<output>` → filtered list (only words with count ≥ 5)

**Example usage:**
```bash
./step3_split_final_search_term_to_words.sh final_terms.tsv tokens.tsv
```

**Output files:**
```
tokens.tsv
w2cnt_tokens.tsv
sorted_w2cnt_tokens.tsv
filtered_tokens.tsv
```

---

## 🧠 Pipeline Summary

| Step | Script | Description | Input | Output |
|------|---------|-------------|--------|---------|
| 1 | `step1_download.sh` | Download Amazon QAC dataset from Hugging Face | — | Local dataset folder |
| 2 | `step2_extract_final_serach_term_from_data.sh` | Extract `final_search_term` column from parquet files | Dataset folder | `final_terms.tsv` |
| 3 | `step3_split_final_search_term_to_words.sh` | Tokenize and compute word frequencies | `final_terms.tsv` | Token and frequency TSVs |

---

## ⚙️ Dependencies

Ensure these are installed before running:
- `curl`
- `jq`
- `parquet-tools`
- GNU `awk`, `sort`, and `tr`

To install missing dependencies:
```bash
sudo apt install curl jq parquet-tools coreutils
```

---

## 🚀 Quick Run Example

```bash
# Step 1: Download Amazon QAC dataset
./step1_download.sh

# Step 2: Extract search terms
./step2_extract_final_serach_term_from_data.sh amazonqac_train final_terms.tsv

# Step 3: Tokenize and compute frequencies
./step3_split_final_search_term_to_words.sh final_terms.tsv tokens.tsv
```

---

## 🧾 License
This repository follows the same license as the main `aws_qac_autocomplete` project.
