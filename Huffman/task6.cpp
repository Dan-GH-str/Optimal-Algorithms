#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left, * right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

void buildHuffmanTree(string text, map<char, int>& freq, Node*& root);
void generateCodes(Node* root, string str, map<char, string>& huffmanCode);

int main() {
    setlocale(LC_ALL, "RU");
    string text;
    cout << "Введите текст: ";
    getline(cin, text); // Используем getline для обработки пробелов

    map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    Node* root = nullptr;
    buildHuffmanTree(text, freq, root);

    map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "\nКод Хаффмана:\n";
    for (pair<char, string> pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // Кодирование текста
    string encodedText = "";
    for (char ch : text) {
        encodedText += huffmanCode[ch];
    }

    cout << "\nЗакодированный текст: " << encodedText << ", " << encodedText.length() << " бита" << endl;

    // Декодирование текста
    string decodedText = "";
    Node* curr = root;
    for (char bit : encodedText) {
        if (bit == '0') {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }

        if (!curr->left && !curr->right) {
            decodedText += curr->ch;
            curr = root;
        }
    }


    cout << "\nДекодированный текст: " << decodedText << endl;

    double compressionRatio = (double)encodedText.length() / (text.length() * 8);
    cout << "\nКоэффициент сжатия: " << fixed << setprecision(2) << compressionRatio << " (более низкое значение означает лучшую компрессию)" << endl;


    // Освобождение памяти
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* temp = q.front();
        q.pop();
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
        delete temp;
    }


    return 0;
}

void buildHuffmanTree(string text, map<char, int>& freq, Node*& root) {
    priority_queue<Node*, vector<Node*>, compare> pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        pq.push(top);
    }
    root = pq.top();
}

void generateCodes(Node* root, string str, map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}