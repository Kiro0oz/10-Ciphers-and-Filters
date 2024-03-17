/*
FCAI – Structured Programming – 2024 - Assignment 2
----------------------------------------------------
File: CS112_A2_T4_S17,18_20230295_20230448_20230619
Purpose: 10 Ciphers
Author: Kirollos Adel Samir-S17
        Noura Muhammad Mahmoud-S18
        Eman Emad Abdulrahim-S18
Emails: Kiroadel113@gmail.com
        nouraarafa180@gmail.com
        emanemadfarghaly@gmail.com
ID 1: 20230295- ciphers=>1,3,5
ID 2: 20230448- ciphers=>6,7,8
ID 3: 20230619- ciphers=>0,2,4
*/

#include<bits/stdc++.h>
using namespace std;

string alphabet() {
    string alpha;
    for (int i = 65; i <= 90; ++i)
        alpha += char(i);
    return alpha;
}
string upper_case(string text){
    for(int i=0 ;i<text.length();++i)
        text[i]= toupper(char(text[i]));
    return text;
}
string lower_case(string text){
    for(int i=0 ;i<text.length();++i)
        text[i]= tolower(char(text[i]));
    return text;
}
string removespace(string text){
    for (int i = 0; i < text.length(); ++i){
        if (isspace(text[i]))
            text.erase(text.begin() + i);
    }
    return text;
}
void invalid(string text){
    text=removespace(text);
    for (char i:text){
        if (!isalpha(i)){
            cout<<"Please Enter a Valid Text";
            break;
        }
    }
}

/*=========0.Affine Cipher=========*/
void Affine_Cipher(string text){
    int a,b;
    cout<<"Enter a,b for Encryption Equation\n";
    cin>>a>>b;
    string ciphertext;
    text=upper_case(text);
    for (char i:text){
        for (int x=0;x<26;++x){
        if ( i == alphabet()[x])
            ciphertext += alphabet()[(a*x+b)%26];
        }
    }
    cout<<"The encrypted text is: "<<ciphertext<<endl;
    
}
void Affine_Decipher(string text){
    int c,b;
    cout<<"Enter c ,b for Decryption Equation\n";
    cin>>c>>b;
    string plaintext;
    text=upper_case(text);
    int D;
    for (char i : text){
        for (int y=0;y<26;++y){
            if ( i == alphabet()[y]){
                D = c*(y-b);
                if (D<0){
                    for (int i=1 ;D<0;++i)
                        D+=i*26;
                }
            }
        }
        plaintext += alphabet()[(D%26)];
    }
    cout<< "The Decrypted text is: "<<plaintext;
}


/*=========2.Atbash Cipher=========*/
void Atbash_Cipher_V1(string text){
    string ciphertext;
    string cipheredchars;
    text=upper_case(text);
    
    for (int i=25;i>=0;--i)
        cipheredchars+=alphabet()[i];
    for (char i: text ){
        if (isspace(i))
            ciphertext+=" ";
        else{
            for (int j=0;j<26;++j){
                if ( i == alphabet()[j])
                    ciphertext+=cipheredchars[j];
            }
        }
    }
    cout<<ciphertext;
}
void Atbash_Cipher_V2(string text){
    string g1;
    string g2;
    string ciphertext;

    for (int i=25;i>=0;--i){
        if (i>=13)
            g2+=alphabet()[i];
        else
            g1+=alphabet()[i];
    }
    text=upper_case(text);
    for (char i: text ){
        if (isspace(i))
            ciphertext+=' ';
        else{
            for (int j=0;j<26;++j){
            if ( i == alphabet()[j])
                j<13?ciphertext+=g1[j]:ciphertext+=g2[j-13];
            }
        }
    }
    cout<<ciphertext;
}

/*=========3.Vignere Cipher=========*/
void Vignere_encryption() {
    string user_msg, keyword, res;
    int key_count = 0;
    cout << "Enter your text: ";
    while (true) {
        getline(cin, user_msg);
        if (user_msg.length() <= 1) {
            cout << "Error! Insert a valid text\n";
            continue;
        }
        break;
    }
    cout  << "Enter the keyword: ";
    while (true) {
        cin >> keyword;
        if (keyword.length() <= 1) {
            cout << "Error! Insert a valid keyword\n";
            continue;
        }
        break;
    }
    cin.ignore();
    for(int i = 0; i < user_msg.length(); i++) {
        if (islower(user_msg[i])) {
            user_msg[i] = toupper(user_msg[i]);
        }
        if(user_msg[i] >= 65 && user_msg[i] <= 90) {
            res += ((user_msg[i] + keyword[key_count]) % 26) + 65;
            key_count++;
            if (key_count == keyword.length()) {
                    key_count = 0;
                }
        }
        else {
            res += user_msg[i];
        }
    }

    cout << "Your message: " << user_msg << "\n";
    cout << "The cipherd message is: " << res << "\n";

}


void Vignere_decryption() {
    string user_msg, keyword, res;
    int key_count = 0;
    cout << "Enter your encrypted text: ";
    while (true) {
        getline(cin, user_msg);
        if (user_msg.length() <= 1) {
            cout << "Error! Insert a valid text\n";
            continue;
        }
        break;
    }
    cout  << "Enter the keyword: ";
    while (true) {
        cin >> keyword;
        if (keyword.length() <= 1) {
            cout << "Error! Insert a valid keyword\n";
            continue;
        }
        break;
    }
    cin.ignore();
    for(int i = 0; i < user_msg.length(); i++) {
        if (islower(user_msg[i])) {
            user_msg[i] = toupper(user_msg[i]);
        }
        if(user_msg[i] >= 65 && user_msg[i] <= 90) {
            if(user_msg[i] < keyword[key_count]) {
                res += (user_msg[i] - keyword[key_count]) %26 + 26 + 65;
            } else {
                res += (user_msg[i] - keyword[key_count]) % 26 + 65;
            }
            key_count++;
            if (key_count == keyword.length()) {
                key_count = 0;
            }
        }else {
            res += user_msg[i];
        }
    }

    cout << "Your message: " << user_msg << "\n";
    cout << "The cipherd message is: " << res << "\n";

}
/*=========4.Baconian Cipher=========*/
void Baconian_Cipher(string text) {
    string ciphertext;
    text=upper_case(text);
    for (char i : text) {
        string cipherchar,indexes;
        for (int j = 0; j < 26; ++j) {
            if (i == alphabet()[j]) {
                for (int x = 0; x < 5; ++x) {
                    if (j % 2 == 0)
                        indexes += 'a';
                    else
                        indexes += 'b';
                    j /= 2; 
                }
                for (int i=5;i>=0;--i){
                    cipherchar+=indexes[i];
                }
                ciphertext += cipherchar+' ';
                break;
            }
        }
    }
    cout << ciphertext;
}
void Baconian_Decipher(string text) {
    string plaintext;
    string alpha = alphabet();
    text=removespace(text);
    text=lower_case(text);
    for(char i : text){
        if(i!='a' && i!='b'){
            cout<<"Please Enter A Valid Baconian Cipher\n";
            break;
        }
    }
    for (size_t i = 0; i < text.length(); i += 5) {
        string cipherchar = text.substr(i, 5);
        int index = 0;
        for (int j = 0; j < 5; ++j) {
            index *= 2;
            if (cipherchar[j] == 'b') {
                index += 1;
            }
        }
        
        char plainchar = alpha[index];
        plaintext += plainchar;
    }
    
    cout<<plaintext;
    
}







/*=========5.Simple Substitution=========*/
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

/*=========6.Morse Code==========*/
bool isNotEmpty(const string& str) {
    return !str.empty();
}

string Morse_code_Encryption(const string& message) {
    string cleaned_message;
    string result;

    for (char ch : message) {
        if (isalpha(ch) || ch == ' ') {
            char lowercase_ch = tolower(ch);
            cleaned_message += lowercase_ch;
            switch (lowercase_ch) {
                case 'a': result += ".- "; break;
                case 'b': result += "-... "; break;
                case 'c': result += "-.-. "; break;
                case 'd': result += "-.. "; break;
                case 'e': result += ". "; break;
                case 'f': result += "..-."; break;
                case 'g': result += "--. "; break;
                case 'h': result += ".... "; break;
                case 'i': result += ".. "; break;
                case 'j': result += ".--- "; break;
                case 'k': result += "-.- "; break;
                case 'l': result += ".-.. "; break;
                case 'm': result += "-- "; break;
                case 'n': result += "-. "; break;
                case 'o': result += "--- "; break;
                case 'p': result += ".--. "; break;
                case 'q': result += "--.- "; break;
                case 'r': result += ".-. "; break;
                case 's': result += "... "; break;
                case 't': result += "- "; break;
                case 'u': result += "..- "; break;
                case 'v': result += "...- "; break;
                case 'w': result += ".-- "; break;
                case 'x': result += "-..- "; break;
                case 'y': result += "-.-- "; break;
                case 'z': result += "--.. "; break;
                case ' ': result += "   "; break;
                default: break; // Ignore non-alphabetic characters
            }
        } else {
            cout << "Error: Please enter a valid message with letters only and Try Again." << endl;
            return ""; // Return an empty string to indicate error
        }
    }

    return result;
}

string getcode(const string& morse_code) {
    if (morse_code == ".-") return "a";
    if (morse_code == "-...") return "b";
    if (morse_code == "-.-.") return "c";
    if (morse_code == "-..") return "d";
    if (morse_code == ".") return "e";
    if (morse_code == "..-.") return "f";
    if (morse_code == "--.") return "g";
    if (morse_code == "....") return "h";
    if (morse_code == "..") return "i";
    if (morse_code == ".---") return "j";
    if (morse_code == "-.-") return "k";
    if (morse_code == ".-..") return "l";
    if (morse_code == "--") return "m";
    if (morse_code == "-.") return "n";
    if (morse_code == "---") return "o";
    if (morse_code == ".--.") return "p";
    if (morse_code == "--.-") return "q";
    if (morse_code == ".-.") return "r";
    if (morse_code == "...") return "s";
    if (morse_code == "-") return "t";
    if (morse_code == "..-") return "u";
    if (morse_code == "...-") return "v";
    if (morse_code == ".--") return "w";
    if (morse_code == "-..-") return "x";
    if (morse_code == "-.--") return "y";
    if (morse_code == "--..") return "z";
    return "";
}

bool isValidMorseCharacter(char ch) {
    // Valid Morse code characters: . - /
    return (ch == '.' || ch == '-' || ch == '/');
}

bool isValidMorseCode(const string& code) {
    for (char ch : code) {
        if (!isValidMorseCharacter(ch) && ch != ' ') {
            return false;
        }
    }
    return true;
}
string Morse_code_Decryption() {

    string echar_morse, result, message;
    int u = 0, count_space = 0;
    cout << "Enter Your Encrypted Text:\n";
    getline(cin, message);

    // Check if the input is valid Morse code
    if (!isValidMorseCode(message) || message.empty()) {
        cout << "Error: Input is not a Morse code, Please Try Again." << endl;
        return ""; // Return an empty string to indicate error
    }

    for (int i = 0; i < message.length() - 1; i++) {
        if (message[i] == ' ' && message[i + 1] != ' ') {
            for (int x = u; x < i; x++) {
                echar_morse += message[x];
            }
            u = i + 1;
            result += getcode(echar_morse);
            echar_morse = "";
        }

        // This to count the spaces and add space to the result and ignore other spaces
        if (message[i] == ' ' && message[i + 1] == ' ') {
            while (message[i] == ' ') {
                i += 1;
                count_space++;
            }
            for (int x = u; x < i - count_space; x++) {
                echar_morse += message[x];
            }
            u = i + 1;
            result += getcode(echar_morse);
            echar_morse = "";
            result += " ";
            u--;
        }
        count_space = 0;
    }

    echar_morse = "";
    for (int x = u; x < message.length(); x++) {
        echar_morse += message[x];
    }
    echar_morse.erase(remove(echar_morse.begin(), echar_morse.end(), ' '), echar_morse.end());
    result += getcode(echar_morse);
    result += "\n";

    cout << "Decrypted Text:\n" << result;
    return result; // Return the decrypted text
}



/*=========8.Xor=========*/

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



/*=========9.Rail-Fence=========*/

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
        if (input.size() != 1 || (input[0] != '1' && input[0] != '2' && input[0] != '3')) {
            cout << "Invalid input. Please enter '1' for Cipher, '2' for Decipher, or '3' for Exit." << endl;
            continue;
        }

        if (!isNotEmpty(input) || !isdigit(input[0]) || !isValidChoice(input[0])) {
            cout << "Invalid input. Please enter '1' for Cipher, '2' for Decipher, or '3' for Exit." << endl;
            continue;
        }

        choice = input[0];

        if (choice == '1') {
            cout << "Which Cipher do you like to choose?" << endl;
            cout << "\n==========================\n";
            cout << "0) Affine\n";
            cout << "1) Route\n";
            cout << "2) Atbash\n";
            cout << "3) Vigenere\n";
            cout << "4) Baconian\n";
            cout << "5) Simple Substitution\n";
            cout << "6) Polybius Square\n";
            cout << "7) Morse Code\n";
            cout << "8) Xor\n";
            cout << "9) Rail-Fence\n";
            cout << "===========================\n";
            cout << "Choose an option : ";
            getline(cin, input);

            if (input.size() != 1 || input[0] !='0' && input[0] != '1' && input[0] !='2' && input[0] != '3' &&
                                     input[0] != '4' && input[0] !='5' && input[0] != '6' &&input[0] != '7' &&
                                     input[0] !='8' && input[0] != '9') {
                cout << "Invalid input. Please Try Again." << endl;
                continue;
            }
            
            if (!isNotEmpty(input) || !isdigit(input[0]) || (input[0] <= '0' || input[0] > '9')) {
                cout << "Invalid input. Please enter a number in the range[0-9]." << endl;
                continue;
            }

            n = input[0];

            if(n == '0') {
                cout << "> Affine Cipher <\n";
                // func
            }

            else if (n == '1') {
                cout << "> Route Cipher <\n";
                // func
            }

            else if(n == '2') {
                cout << "> Atbash Cipher <\n";
                // func
            }

            else if (n == '3') {
                cout << "> Vignere Cipher <\n";
                Vignere_encryption();
            }

            else if(n == '4') {
                cout << "> Baconian Cipher <\n";
                // func
            }

            else if (n == '5') {
                cout << "> Simple Substitution Cipher <\n";
                Encryption();
            }

            else if (n == '6') {
                cout << "> Polybius Cipher <\n";
                // func
            }

            else if(n == '7') {
                cout << "> Morse Code Cipher <\n";
                string message;
                cout <<  "* Enter Your Plain Text : " << endl;
                getline(cin , message);
                cout<< "Encrypted Text: " << Morse_code_Encryption(message);
            }

            else if (n == '8') {
                cout << "> Xor Cipher <\n";
                xordecipher();

            }

            else if (n == '9') {
                cout << "> Rail-Fence Cipher <\n";
                string text;
                cout << "* Enter Your Plain Text : " << "\n";
                getline(cin, text);
                cout << "Encrypted Text: " << encrypt_Rail_Fence(text) << "\n";
            }

            else {
                cout << "Invalid: please Enter a number in range[0-9].." << endl;
                continue;
            }

        } else if (choice == '2') {
            cout << "Which Decipher do you like to choose?" << endl;
            cout << "\n==========================\n";
            cout << "0) Affine\n";
            cout << "1) Route\n";
            cout << "2) Atbash\n";
            cout << "3) Vigenere\n";
            cout << "4) Baconian\n";
            cout << "5) Simple Substitution\n";
            cout << "6) Polybius Square\n";
            cout << "7) Morse Code\n";
            cout << "8) Xor\n";
            cout << "9) Rail-Fence\n";
            cout << "===========================\n";
            cout << "Choose an option : ";
            getline(cin, input);

            if (input.size() != 1 || input[0] !='0' && input[0] != '1' && input[0] !='2' && input[0] != '3' &&
                                     input[0] != '4' && input[0] !='5' && input[0] != '6' &&input[0] != '7' && input[0] !='8' && input[0] != '9') {
                cout << "Invalid input. Please Try Again." << endl;
                continue;
            }

            if (!isNotEmpty(input) || !isdigit(input[0]) || (input[0] <= '0' || input[0] >= '9')) {
                cout << "Invalid input. Please enter a number in the range[0-9]." << endl;
                continue;
            }

            n = input[0];

            if(n == '0') {
                cout << "> Affine Decipher <\n";
                // func
            }

            else if (n == '1') {
                cout << "> Route Decipher <\n";
                // func
            }

            else if(n == '2') {
                cout << "> Atbash Decipher <\n";
                // func
            }

            else if (n == '3') {
                cout << "> Vignere Decipher <\n";
                Vignere_decryption();
            }

            else if(n == '4') {
                cout << "> Baconian Decipher <\n";
                // func
            }

            else if (n == '5') {
                cout << "> Simple Substitution Decipher <\n";
                Decryption();
            }

            else if (n == '6') {
                cout << "> Polybius Decipher <\n";
                // func
            }

            else if(n == '7') {
                cout << "> Morse Code Decipher <\n";
                Morse_code_Decryption();
            }

            else if (n == '8') {
                cout << "> Xor Decipher <\n";
                xordecipher();

            }

            else if (n == '9') {
                cout << "> Rail-Fence Decipher <\n";
                string text;
                cout << "* Enter Your Encrypted Text : " << endl;
                getline(cin, text);
                cout <<"Decrypted Text: " << decrypt_Rail_Fence(text) << endl;
            }

            else {
                cout << "Invalid: please Enter a number in range[0-9].." << endl;
                continue;
            }
        } else if (choice == '3') {
            cout << "Bye!!";
            break;
        }
    }

    return 0;
}
