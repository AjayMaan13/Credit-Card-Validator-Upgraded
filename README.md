# 💳 Credit Card Validator Upgraded

[![C](https://img.shields.io/badge/C-A8B9CC?logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![OpenSSL](https://img.shields.io/badge/OpenSSL-721412?logo=openssl&logoColor=white)](https://www.openssl.org/)
[![cURL](https://img.shields.io/badge/cURL-073551?logo=curl&logoColor=white)](https://curl.se/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Advanced credit card management system with military-grade encryption, real-time API integration, and professional logging using OpenSSL, cURL, and JSON technologies.

## 🎯 Features

- 🔐 **Military-Grade Security** - AES-256-CBC encryption for secure card data storage
- 🌐 **Real-Time API Integration** - BIN database validation for card verification  
- 📝 **Professional Logging** - JSON-structured audit trails for compliance
- 💳 **Advanced Validation** - Luhn algorithm with automatic card type detection
- 📊 **Activity Monitoring** - Complete operation history with forensic analysis
- 🛡️ **Memory Safety** - Zero memory leaks with secure memory management

## 🛠️ Tech Stack

**Core:** C programming with OpenSSL, cURL, cJSON libraries  
**Security:** AES-256-CBC encryption, Base64 encoding, secure key management  
**Network:** RESTful API integration, HTTP client implementation  
**Data:** JSON parsing/generation, encrypted file persistence, structured logging

## 🚀 Quick Start

### Installation & Build
```bash
# Ubuntu/Debian: sudo apt install libcjson-dev libcurl4-openssl-dev
# macOS: brew install curl openssl

git clone https://github.com/AjayMaan13/Credit-Card-Validator-Upgraded.git
cd Credit-Card-Validator-Upgraded
gcc main.c encrypt.c api.c logger.c credit.c cJSON.c -o main -lcurl -lssl -lcrypto
./main
```

## 📁 Structure

```
Credit-Card-Validator-Upgraded/
├── main.c              # Entry point and menu system
├── credit.c/.h         # Luhn validation & card logic
├── openssl_crypto.c/.h # AES encryption/decryption  
├── api.c/.h            # cURL BIN API integration
├── logger.c/.h         # JSON activity logging
├── cJSON.c/.h          # JSON parsing library
└── cards.json          # Encrypted card storage
```

## 💻 Usage Examples

### Interactive Menu
```
======= CARD VALIDATOR MENU =======
1. ✅ Check Card Validity & Type
2. 🌐 Lookup Card Info via API  
3. 📜 View Encrypted Card History
4. ➕ Add New Card
0. ❌ Exit
===================================
```

### Encryption Implementation
```c
// AES-256-CBC encryption with secure key management
void encrypt_data(const unsigned char *plaintext, int plaintext_len,
                  unsigned char *ciphertext, int *ciphertext_len,
                  const unsigned char *key, const unsigned char *iv);

// Original: 4003600000000014
// Encrypted: rph5a5jmSHBvApToINAYKg==
```

### API Integration
```c
// Real-time BIN lookup 
void lookup_card_info(const char *card_number) {
    snprintf(url, sizeof(url), "https://lookup.binlist.net/%.6s", card_number);
    cJSON *json = cJSON_Parse(response);
}
```

## 🏗️ Architecture

### Security Features
- **AES-256-CBC Encryption** - Military-grade card data protection
- **Secure Key Management** - Proper IV handling and Base64 encoding  
- **Input Sanitization** - Prevents injection attacks and buffer overflows
- **Memory Safety** - Comprehensive cleanup and bounds checking

### API Integration Flow
1. **Input Validation** → Luhn Algorithm → Card Type Detection
2. **API Request** → HTTP/cURL → BIN Database Lookup → JSON Response
3. **Data Processing** → Encryption → Storage → Activity Logging

## 🧪 Testing

```bash
# Memory leak testing
valgrind --leak-check=full ./main

# Expected: Zero memory leaks, proper SSL cleanup
```

**Sample API Response:**
```
Enter Card Number: 4003600000000014
🛰 BIN Info:
  Scheme: visa
  Brand: VISA  
  Type: debit
  Bank: JPMorgan Chase Bank, N.A.
```

## 📊 Stats

- **Production-ready** C application with enterprise features
- **Zero memory leaks** verified with Valgrind testing
- **Military-grade** AES-256-CBC encryption implementation  
- **Real-time API** integration with error handling
- **JSON logging** suitable for production monitoring

## 👨‍💻 Author

**Ajaypartap Singh Maan**  
[GitHub](https://github.com/AjayMaan13) • [LinkedIn](https://linkedin.com/in/ajaypartap-singh-maan) • ajayapsmaanm13@gmail.com

---

⭐ **Star if helpful!**
