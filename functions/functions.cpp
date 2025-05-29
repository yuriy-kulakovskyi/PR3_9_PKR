#include <iostream>
#include "./functions.h"

using namespace std;


void PrintTree(Node* root, int level)
{
    if (root != NULL)
    {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << "    ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

// Виведення бінарного дерева з виділенням певного елемента
void PrintTreeWithHighlight(Node* root, int level, int highlight_value)
{
    if (root == NULL)
        return;

    // Збільшуємо відступ для наступного рівня
    const int INDENT = 4;
    level += INDENT;

    // Спочатку виводимо праве піддерево (воно буде зверху)
    PrintTreeWithHighlight(root->right, level, highlight_value);

    // Потім виводимо сам корінь
    cout << endl;
    for (int i = INDENT; i < level; i++)
        cout << " ";

    if (root->info == highlight_value) {
        cout << "[" << root->info << "]";
    }
    else {
        cout << root->info;
    }

    // Нарешті виводимо ліве піддерево (воно буде знизу)
    PrintTreeWithHighlight(root->left, level, highlight_value);
}

// Обчислення висоти дерева
int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

// Обчислення фактора балансування
int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

// Функція правої ротації
void RightRotation(Node*& root)
{
    Node* tmp1 = root->left;
    Node* tmp2 = tmp1->right;
    tmp1->right = root;
    root->left = tmp2;
    root = tmp1;
}

// Функція лівої ротації
void LeftRotation(Node*& root)
{
    Node* tmp1 = root->right;
    Node* tmp2 = tmp1->left;
    tmp1->left = root;
    root->right = tmp2;
    root = tmp1;
}

// Функція для знаходження максимального елемента
Node* FindMin(Node* root)
{
    if (root->right != NULL)
        return FindMin(root->right);
    else
        return root;
}

// Видалення всього дерева
void DeleteTree(Node*& root)
{
    if (root != NULL)
    {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
        root = NULL;
    }
}

// Постфіксний обхід з виділенням елемента
void PostfixOrderWithHighlight(Node* root, int highlight_value)
{
    if (root != NULL)
    {
        // Постфіксний обхід: ліве піддерево -> праве піддерево -> корінь
        PostfixOrderWithHighlight(root->left, highlight_value);
        PostfixOrderWithHighlight(root->right, highlight_value);

        if (root->info == highlight_value) {
            cout << "[" << root->info << "] ";
        }
        else {
            cout << root->info << " ";
        }
    }
}

// Постфіксний обхід для пошуку першого мінімального елемента
void PostfixOrderWithMin(Node* root, Node*& minNode)
{
    if (root != NULL) {
        // Постфіксний обхід: знизу вгору
        PostfixOrderWithMin(root->left, minNode);
        PostfixOrderWithMin(root->right, minNode);

        // Зберігаємо перший мінімальний елемент
        if (minNode == NULL || root->info < minNode->info) {
            minNode = root;
        }
    }
}

// ПУНКТ 1: Функція для створення бінарного дерева із заданою кількістю елементів
Node* CreateTree(int nodeCount)
{
    if (nodeCount == 0)
        return NULL;
    else
    {
        Node* newNode = new Node;
        cout << " Введіть значення вузла: ";
        cin >> newNode->info;
        int leftCount = nodeCount / 2;
        int rightCount = nodeCount - leftCount - 1;
        newNode->left = CreateTree(leftCount);
        newNode->right = CreateTree(rightCount);
        return newNode;
    }
}

// ПУНКТ 3, 4: Функція для додавання елемента до бінарного дерева пошуку
Node* BinarySearchInsert(Node*& root, Info value, bool& found)
{
    if (root == NULL)
    {
        root = new Node;
        root->info = value;
        root->left = NULL;
        root->right = NULL;
        found = false;
        return root;
    }
    else
        if (value == root->info)
        {
            found = true;
            return root;
        }
        else
            if (value < root->info)
                return BinarySearchInsert(root->left, value, found);
            else
                return BinarySearchInsert(root->right, value, found);
}

// ПУНКТ 5: Функція балансування бінарного дерева пошуку
void BalanceHeight(Node*& root)
{
    if (root != NULL)
    {
        while (BFactor(root) >= 2)
        {
            if (BFactor(root->right) < 0)
                RightRotation(root->right);
            LeftRotation(root);
        }
        while (BFactor(root) <= -2)
        {
            if (BFactor(root->left) > 0)
                LeftRotation(root->left);
            RightRotation(root);
        }
        BalanceHeight(root->left);
        BalanceHeight(root->right);
    }
}

// ПУНКТ 6, 7, 8: Функція видалення вузла з бінарного дерева пошуку
Node* BinarySearchDelete(Node* root, Info value)
{
    if (NULL == root) return NULL;
    if (root->info == value)
    {
        // ПУНКТ 6: Видалення листового вузла (без дочірніх)
        if (NULL == root->left && NULL == root->right)
        {
            delete root;
            return NULL;
        }
        // ПУНКТ 7: Видалення вузла з одним дочірнім (лівим)
        if (NULL == root->right && root->left != NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // ПУНКТ 7: Видалення вузла з одним дочірнім (правим)
        if (NULL == root->left && root->right != NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // ПУНКТ 8: Видалення вузла з двома дочірніми
        root->info = FindMin(root->left)->info;
        root->left = BinarySearchDelete(root->left, root->info);
        return root;
    }
    if (value < root->info)
    {
        root->left = BinarySearchDelete(root->left, value);
        return root;
    }
    if (value > root->info)
    {
        root->right = BinarySearchDelete(root->right, value);
        return root;
    }
    return root;
}

// ПУНКТ 10: Декоратор для знаходження першого мінімального елемента
void FindFirstMin(Node* root)
{
    Node* minNode = NULL;
    PostfixOrderWithMin(root, minNode);

    if (minNode != NULL) {
        cout << "Перший елемент з мінімальним значенням: " << minNode->info << endl;
        cout << "Дерево з виділеним елементом: ";
        PrintTreeWithHighlight(root, 0, minNode->info);

        cout << "\nПостфіксний обхід з виділеним елементом: ";
        PostfixOrderWithHighlight(root, minNode->info);
        cout << endl;
    }
    else {
        cout << "Бінарне дерево порожнє" << endl;
    }
}

// Функція для відображення меню
void showMenu() {
    cout << "\n======== Меню операцій з бінарним деревом ========\n";
    cout << "1. Створити нове бінарне дерево з вказаною кількістю елементів\n";
    cout << "2. Відобразити бінарне дерево\n";
    cout << "3. Створити бінарне дерево пошуку з вказаною кількістю елементів\n";
    cout << "4. Додати новий елемент до бінарного дерева пошуку\n";
    cout << "5. Збалансувати бінарне дерево пошуку\n";
    cout << "6. Видалити листовий вузол (без дочірніх)\n";
    cout << "7. Видалити вузол з одним дочірнім\n";
    cout << "8. Видалити вузол з двома дочірніми\n";
    cout << "9. Видалити вузол з усіма його дочірніми (видалити піддерево)\n";
    cout << "10. Знайти перший елемент з мінімальним значенням (постфіксний обхід)\n";
    cout << "0. Вихід\n";
    cout << "Ваш вибір: ";
}