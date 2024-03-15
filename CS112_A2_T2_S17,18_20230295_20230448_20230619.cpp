/*
Authors: Kirollos Adel Samir -20230295 - Simple Substitution Cipher.
         Noura Muhammad Mahmoud - 20230448 - Xor Cipher.
         Eman Emad Abdulrahim- 20230619 - Rail fence Cipher.
Version: 8.0
*/

#include<bits/stdc++.h>
using namespace std;


/*=========Simple Substitution=========*/

// Get the alphabet after adding the word
vector<char> add_key_to_alpha(string key){
    vector<char> alpha ;
    for (int i = 0 ; i < key.length() ; i++){ // Add the key to the alpha variable
        alpha.push_back(key[i]) ;
    }
    // Here (i) start from 65 which is letter A in ASCII code to 90 " letter Z in ASCII code "
    for (int i = 65 ; i <= 90 ; i++){
        auto search = find(alpha.begin() , alpha.end() , i) ; // search for the letters of key i alphabet
        if (search == alpha.end()){
            alpha.push_back(i) ;
        }
    }
    return alpha;
}

bool is_unique(string key) { // check if there is multiple letters in the word
    for(int i = 0; i < key.length(); i++) {
        for(int j = i + 1; j < key.length(); j++) {
            if(key[i] == key[j]) {
                return false;
            }
        }
    }
    return true;
}

void Encryption() {
    string res, user_msg, key;
    vector<char> cipher_txt;
    cout << "* Enter your plain text: ";
    while (true) {
        getline(cin, user_msg);
        if (user_msg.length() == 0) {
            cout << "Error! Insert a valid text: ";
            continue;
        }
        break;
    }

    cout << "* Enter the key ( should be 5 unique letters ):  ";
    while (true) {
        cin >> key;
        cin.ignore();
        if(key.length() != 5 || key.length() == 0) { // check if the length of the word is less than 5
            cout << "Error! Insert the valid key: ";
            continue;
        }
        // Covert letters of the key to Uppercase
        string upper_key;
        for(int i = 0; i < key.length();i++) {
            if(islower(key[i])) {
                upper_key += toupper(key[i]);
            } else {
                upper_key += key[i];
            }
        }

        if(is_unique(key)) { // add the key to the cipher_txt variable
            cipher_txt = add_key_to_alpha(upper_key);
            break;
        } else {
            cout << "Key is Not UNIQUE\n";
            cout << "Insert the key again: ";
            continue;
        }

    }

    for(int i = 0; i < user_msg.length(); i++) {
        if(islower(user_msg[i])) { // check if text is lowercase to convert it to uppercase
            user_msg[i] = toupper(user_msg[i]);
        }
        if(user_msg[i] >= 65 && user_msg[i] <= 90) { // Encrypted the text
            res += cipher_txt[user_msg[i] - 65];
        } else if(isspace(user_msg[i])) {
            res += user_msg[i];
        } else {
            continue;
        }
    }
    // Get the cipher lowercase text
    string lower_res;
    for(int i = 0; i < res.length();i++) {
        lower_res += tolower(res[i]);
    }

    cout <<"\nThe Plain Text is: " << user_msg;
    cout <<"\nThe Cipher Text is: " << lower_res;
}

void Decryption() {
    string res, user_txt, key;
    vector<char> decryp_txt;
    cout << "* Enter your Encrypted Message: ";
    while (true) {
        getline(cin, user_txt);
        if (user_txt.length() == 0) {
            cout << "Error! Insert a valid text: ";
            continue;
        }
        break;
    }

    cout << "* Enter the key ( should be 5 unique letters ):  ";
    while (true) {
        cin >> key;
        cin.ignore();
        if(key.length() != 5 || key.length() == 0) {
            cout <<"Error! Insert the valid key: ";
            continue;
        }
        string upper_key;
        for(int i = 0; i < key.length();i++) {
            if(islower(key[i])) {
                upper_key += toupper(key[i]);
            } else {
                upper_key += key[i];
            }
        }
        if(is_unique(key)) {
            decryp_txt = add_key_to_alpha(upper_key);
            break;
        } else {
            cout << "Key is Not UNIQUE\n";
            cout << "Insert the key again: ";
            continue;
        }

    }

    for(int i = 0; i < user_txt.length();i++) {
        if(islower(user_txt[i])) {
            user_txt[i] = toupper(user_txt[i]);
        }
        // Decipher the text by remove the key from the alphabet
        if(user_txt[i] >= 65 && user_txt[i] <= 90) {
            auto fnd = find(decryp_txt.begin(), decryp_txt.end(), user_txt[i]);
            int index = fnd - decryp_txt.begin();
            res += index + 65;
        } else if (isspace(user_txt[i])) {
            res += user_txt[i];
        } else {
            continue;
        }
    }
    string lower_res;
    for(int i = 0; i < res.length();i++) {
        lower_res += tolower(res[i]);
    }
    cout << "\nThe Encryption Text is: " << user_txt;
    cout << "\nThe Plain Text is: " << lower_res;
}

/*=========Xor=========*/

// Function to check if the input is not empty
bool isNotEmpty(const string& str) {
    return !str.empty();
}
// Function to get non-empty input from the user
string getNonEmptyInput(const string& prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
    } while (!isNotEmpty(input));
    return input;
}


bool isValidChoice(char choice) {
    return choice == '1' || choice == '2' || choice == '3';
}

bool isLettersOnly(const string& str) {
    for (char ch : str) {
        if (!isalpha(ch)) {
            return false;
        }
    }
    return true;
}

string xor_cipher(const string& plainText, const string& SecretKey) {
    string result;
    size_t keyLength = SecretKey.length();
    for (size_t i = 0; i < plainText.length(); ++i) {
        result += plainText[i] ^ SecretKey[i % keyLength];
    }
    return result;
}


string stringToHex(const string& plainText) {
    stringstream hexStream;
    hexStream << hex << uppercase << setfill('0');
    for (char ch : plainText) {
        hexStream << setw(2) << static_cast<int>(static_cast<unsigned char>(ch));
    }
    return hexStream.str();
}

string decipherText(const string& hexMsg, const string& key) {
    string result;
    for (size_t i = 0; i < hexMsg.length(); i += 2) {
        string byte = hexMsg.substr(i, 2);
        unsigned int byteValue;
        istringstream(byte) >> hex >> byteValue;
        result += byteValue ^ key[i / 2 % key.length()];
    }
    return result;
}

void xorcipher() {
    string SecretKey;
    string plainText;
    cout << "* Enter Your Plain Text : " << endl;
    getline(cin, plainText);
    do {
        SecretKey = getNonEmptyInput("Enter The Secret Key (letters only): ");
    } while (!isLettersOnly(SecretKey));
    string Ciphered_Textt = xor_cipher(plainText, SecretKey);
    string Ciphered_TextH = stringToHex(Ciphered_Textt);

    cout << "Ciphered Message (Text) : " << Ciphered_Textt << endl;
    cout << "Ciphered Message (Hex) : " << Ciphered_TextH << endl;
}
//a function to check if a string is a valid Hexadecimal representation

bool isHex(const string& str) {
    return str.find_first_not_of("0123456789ABCDEFabcdef") == string::npos;
}

void xordecipher() {
    while (true) {
        string Hexmsg;
        string SecretKey;
        cout << "* Enter Your Encrypted Message : " << endl;
        getline(cin, Hexmsg);

        //validation for Hex input.
        if (!isHex(Hexmsg)) {
            cout << "Invalid Hexadecimal input" << endl;
            continue;
        }
        do {
            SecretKey = getNonEmptyInput("Enter The Secret Key (letters only): ");
        } while (!isLettersOnly(SecretKey));

        cout << "Your Message is : " << decipherText(Hexmsg, SecretKey);
        break;
    }
}
/*=========Rail-Fence=========*/

// Function to encrypt text using Rail Fence Cipher
string encrypt_Rail_Fence(string text) {
    string ciphertext;
    // store characters in 3 rails
    string rail_arr[3];

    // Iterate on each character in the text to remove spaces and convert to lowercase
    for (int i = 0; i < text.length(); ++i) {
        if (isspace(text[i]))
            text.erase(text.begin() + i);
        text[i] = tolower(char(text[i]));
    }

    int nrow = 0;
    bool nextrow = false; // Flag to determine if moving up or down

    for (char i : text) {
        rail_arr[nrow] += i; // Add character to the current rail
        if (nrow == 0 || nrow == 2) // If at top or bottom rail, change direction
            nextrow = !nextrow; // changing the direction
        (nextrow) ? ++nrow : --nrow;
    }

    // Get ciphertext by combining characters from the 3 rails
    for (int i = 0; i < 3; ++i)
        ciphertext += rail_arr[i];

    return ciphertext;
}

// Function to decrypt text encrypted using Rail Fence Cipher
string decrypt_Rail_Fence(string ciphertext) {
    string decryptedtext(ciphertext.length(), ' '); // Initialize decrypted text with spaces
    int index = 0; // Index for iterating through ciphertext characters

    for (int i = 0; i < 3; i++) {
        int pos = i; // Position in the rail
        bool nextrow = true; // Flag to determine direction

        // Decoding characters for the current rail
        while (pos < ciphertext.length()) {
            decryptedtext[pos] = ciphertext[index++]; // Fill in the decrypted text
            if (i == 0 || i == 2)
                pos += 4; // Jumping to next character in the rail
            else {
                if (nextrow)
                    pos += 2 * (2 - i); // Moving diagonally up
                else
                    pos += 2 * i; // Moving diagonally down
                nextrow = !nextrow; // changing the direction
            }
        }
    }
    return decryptedtext;
}

//Main Program:
int main() {
    cout << "--Welcome User--" << endl;
    cout << "What do you want to be applied to your Message? " << endl;

    while (true) {
        char n;
        char choice;
        string input;

        cout << "\n==========================\n";
        cout << "1) Cipher\n";
        cout << "2) Decipher\n";
        cout << "3) Exit\n";
        cout << "============================\n";
        cout << "Choose an option: ";
        getline(cin, input);

        if (!isNotEmpty(input) || !isdigit(input[0]) || !isValidChoice(input[0])) {
            cout << "Invalid input. Please enter '1' for Cipher, '2' for Decipher, or '3' for Exit." << endl;
            continue;
        }

        choice = input[0];

        if (choice == '1') {
            cout << "Which Cipher do you like to choose?" << endl;
            cout << "\n==========================\n";
            cout << "1) Simple Substitution\n";
            cout << "2) Xor\n";
            cout << "3) Rail-Fence\n";
            cout << "===========================\n";
            cout << "Choose an option : ";
            getline(cin, input);

            if (!isNotEmpty(input) || !isdigit(input[0]) || (input[0] < '1' || input[0] > '3')) {
                cout << "Invalid input. Please enter a number in the range[1-3]." << endl;
                continue;
            }

            n = input[0];

            if (n == '1') {
                cout << "> Simple Substitution Cipher <\n";
                Encryption();
            } else if (n == '2') {
                cout << "> Xor Cipher <\n";
                xorcipher();
            } else if (n == '3') {
                cout << "> Rail-Fence Cipher <\n";
                string text;
                cout << "* Enter Your Plain Text : " << endl;
                getline(cin, text);
                cout << "Encrypted Text: " << encrypt_Rail_Fence(text) << endl;
            } else {
                cout << "Invalid: please Enter a number in range[1-3].." << endl;
                continue;
            }
        } else if (choice == '2') {
            cout << "Which Decipher do you like to choose?" << endl;
            cout << "==========================\n";
            cout << "1) Simple Substitution\n";
            cout << "2) Xor\n";
            cout << "3) Rail-Fence\n";
            cout << "============================\n";
            cout << "Choose an option : ";
            getline(cin, input);

            if (!isNotEmpty(input) || !isdigit(input[0]) || (input[0] < '1' || input[0] > '3')) {
                cout << "Invalid input. Please enter a number in the range[1-3]." << endl;
                continue;
            }

            n = input[0];

            if (n == '1') {
                cout << "> Simple Substitution Decipher <\n";
                Decryption();
            } else if (n == '2') {
                cout << "> Xor Decipher <\n";
                xordecipher();
            } else if (n == '3') {
                cout << "> Rail-Fence Decipher <\n";
                string text;
                cout << "* Enter Your Encrypted Text : " << endl;
                getline(cin, text);
                cout << "Decrypted Text: " << decrypt_Rail_Fence(text) << endl;
            } else {
                cout << "Invalid: please Enter a number in range[1-3].." << endl;
                continue;
            }
        } else if (choice == '3') {
            cout << "Bye!!";
            break;
        }
    }

    return 0;
}
