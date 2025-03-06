#include <iostream>

using namespace std;

class RC4Cipher {
    private:
        static const int STATE_SIZE = 256;
        unsigned char state[STATE_SIZE];
        unsigned char keystream[1024];  
        int keystreamLength;

    

        // KSA Algorithms
        void keyScheduling(const char* key) {
            int keyLen = getStringLength(key);
    
            // Tạo S
            for (int i = 0; i < STATE_SIZE; ++i) {
                state[i] = i;
            }
    
            // Tìm hoán vị khởi tạo của S
            int j = 0;
            for (int i = 0; i < STATE_SIZE; ++i) {
                j = (j + state[i] + key[i % keyLen]) % STATE_SIZE;
                
                // Swap (state[i], state[j])
                unsigned char temp = state[i];
                state[i] = state[j];
                state[j] = temp;
            }
        }

        
    
        // Stream generation
        void generateKeystream(int length) {
            keystreamLength = length;
            int i = 0, j = 0;
    
            for (int k = 0; k < length; ++k) {
                i = (i + 1) % STATE_SIZE;
                j = (j + state[i]) % STATE_SIZE;
    
                // Swap (state[i], state[j])
                unsigned char temp = state[i];
                state[i] = state[j];
                state[j] = temp;
    
                // Generate keystream byte
                int t = (state[i] + state[j]) % STATE_SIZE;
                keystream[k] = state[t];
            }
        }
    
        // Hàm chuyển đổi sang hệ hex
        void byteToHex(unsigned char byte, char* hexStr) {
            char hexChars[] = "0123456789ABCDEF";
            hexStr[0] = hexChars[byte >> 4];
            hexStr[1] = hexChars[byte & 0x0F];
            hexStr[2] = '\0';
        }
    
    public:

        // Tính toán độ dài chuỗi
         int getStringLength(const char* str) {
            int len = 0;
            while (str[len] != '\0') {
            len++;
              }
            return len;
            }


        // Encrypt function
        void encrypt(const char* plaintext, const char* key, unsigned char* ciphertext) {
            int plaintextLen = getStringLength(plaintext);
    
            // Perform key scheduling
            keyScheduling(key);
    
            // Generate keystream
            generateKeystream(plaintextLen);
    
            // Encrypt using XOR
            for (int i = 0; i < plaintextLen; ++i) {
                ciphertext[i] = plaintext[i] ^ keystream[i];
            }
        }
    
        // Print keystream 
        void printKeystream() {
            printf("Keystream (hex): ");
            
            for (int i = 0; i < keystreamLength; ++i) {
                printf("%02X", keystream[i]);  // In từng byte keystream dưới dạng hex
            }
            printf("\n");  
        
        }

        // Print ciphertext
        void printCiphertext(unsigned char* ciphertext, int length){
            printf("Ciphertext (hex): ");
            
            for (int i = 0; i < length; ++i) {
                printf("%02X", ciphertext[i]);  // In từng byte ciphertext dưới dạng hex
            }
            printf("\n");  
        }
        
};
    

    int main() {
        
        RC4Cipher rc4;
    const char* key = "xuanson307204";
    const char* plaintext = "Hanoi University of Science and Technology";
    unsigned char ciphertext[1024] = {0};
    
    rc4.encrypt(plaintext, key, ciphertext);
    printf("Plaintext: %s\n", plaintext);
    printf("Key: %s\n\n", key);
    
    rc4.printKeystream();
    rc4.printCiphertext(ciphertext, rc4.getStringLength(plaintext));
    
    return 0;
    }