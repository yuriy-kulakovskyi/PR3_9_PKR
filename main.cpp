#include <iostream>
#include <iomanip>
#include "./functions/functions.h"

using namespace std;

int main()
{
    Node* root = NULL;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            // ПУНКТ 1: Створення нового бінарного дерева
            if (root != NULL) {
                cout << "Увага: Попереднє дерево буде видалено!" << endl;
                DeleteTree(root); // Очищення попереднього дерева
                root = NULL;
            }

            int N;
            cout << "Кількість вузлів: ";
            cin >> N;

            if (N <= 0) {
                cout << "Кількість вузлів повинна бути більше 0!" << endl;
                break;
            }

            root = CreateTree(N);
            cout << "\nБінарне дерево створено:\n";
            PrintTree(root, 0);
            break;
        }
        case 2: {
            // ПУНКТ 2: Виведення бінарного дерева
            if (root == NULL) {
                cout << "\nДерево порожнє.\n";
            }
            else {
                cout << "\nБінарне дерево:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 3: {
            // ПУНКТ 3: Створення бінарного дерева пошуку
            if (root != NULL) {
                cout << "Увага: Попереднє дерево буде видалено!" << endl;
                DeleteTree(root); // Очищення попереднього дерева
                root = NULL;
            }

            int N;
            cout << "Кількість вузлів: ";
            cin >> N;

            if (N <= 0) {
                cout << "Кількість вузлів повинна бути більше 0!" << endl;
                break;
            }

            Info value;
            bool found = false;

            for (int i = 0; i < N; i++) {
                cout << "Значення #" << i + 1 << ": ";
                cin >> value;
                BinarySearchInsert(root, value, found);
            }

            cout << "\nБінарне дерево пошуку створено:\n";
            PrintTree(root, 0);
            break;
        }
        case 4: {
            // ПУНКТ 4: Додавання нового елемента
            int value;
            cout << "Введіть значення для вставки: ";
            cin >> value;

            bool found = false;
            BinarySearchInsert(root, value, found);

            cout << "\nОновлене дерево:\n";
            PrintTree(root, 0);
            break;
        }
        case 5: {
            // ПУНКТ 5: Збалансування дерева
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого балансувати.\n";
            }
            else {
                BalanceHeight(root);
                cout << "\nЗбалансоване дерево:\n";
                PrintTree(root, 0);
            }
            break;
        }
        case 6: {
            // ПУНКТ 6: Видалення листового вузла
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення для видалення (має бути листовим вузлом): ";
                cin >> value;

                // Перевірка чи є вузол листовим
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool isLeaf = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                        if (current->left == NULL && current->right == NULL) {
                            isLeaf = true;
                        }
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else if (!isLeaf) {
                    cout << "\nВузол зі значенням " << value << " не є листовим.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\nЛистовий вузол видалено. Оновлене дерево:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 7: {
            // ПУНКТ 7: Видалення вузла з одним дочірнім
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення для видалення (має мати рівно одного дочірнього): ";
                cin >> value;

                // Перевірка чи має вузол рівно одного дочірнього
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool hasOneChild = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                        if ((current->left == NULL && current->right != NULL) ||
                            (current->left != NULL && current->right == NULL)) {
                            hasOneChild = true;
                        }
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else if (!hasOneChild) {
                    cout << "\nВузол зі значенням " << value << " не має рівно одного дочірнього.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\nВузол з одним дочірнім видалено. Оновлене дерево:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 8: {
            // ПУНКТ 8: Видалення вузла з двома дочірніми
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення для видалення (має мати два дочірніх): ";
                cin >> value;

                // Перевірка чи має вузол два дочірніх
                Node* current = root;
                Node* parent = NULL;
                bool found = false;
                bool hasTwoChildren = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                        if (current->left != NULL && current->right != NULL) {
                            hasTwoChildren = true;
                        }
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else if (!hasTwoChildren) {
                    cout << "\nВузол зі значенням " << value << " не має двох дочірніх.\n";
                }
                else {
                    root = BinarySearchDelete(root, value);
                    cout << "\nВузол з двома дочірніми видалено. Оновлене дерево:\n";
                    PrintTree(root, 0);
                }
            }
            break;
        }
        case 9: {
            // ПУНКТ 9: Видалення вузла з усіма його дочірніми (видалення піддерева)
            if (root == NULL) {
                cout << "\nДерево порожнє. Нічого видаляти.\n";
            }
            else {
                int value;
                cout << "Введіть значення (вузол та все його піддерево буде видалено): ";
                cin >> value;

                // Пошук вузла
                Node* current = root;
                Node* parent = NULL;
                bool found = false;

                // Пошук вузла та його батьківського вузла
                while (current != NULL && !found) {
                    if (current->info == value) {
                        found = true;
                    }
                    else {
                        parent = current;
                        if (value < current->info) {
                            current = current->left;
                        }
                        else {
                            current = current->right;
                        }
                    }
                }

                if (!found) {
                    cout << "\nВузол зі значенням " << value << " не знайдено.\n";
                }
                else {
                    // Якщо це кореневий вузол, видаляємо все дерево
                    if (parent == NULL) {
                        DeleteTree(root);
                        root = NULL;
                        cout << "\nВсе дерево видалено.\n";
                    }
                    else {
                        // Якщо це лівий дочірній, видаляємо ліве піддерево
                        if (parent->left != NULL && parent->left->info == value) {
                            DeleteTree(parent->left);
                            parent->left = NULL;
                        }
                        // Якщо це правий дочірній, видаляємо праве піддерево
                        else if (parent->right != NULL && parent->right->info == value) {
                            DeleteTree(parent->right);
                            parent->right = NULL;
                        }
                        cout << "\nПіддерево видалено. Оновлене дерево:\n";
                        PrintTree(root, 0);
                    }
                }
            }
            break;
        }
        case 10: {
            // ПУНКТ 10: Знаходження першого елемента з мінімальним значенням у постфіксному обході
            if (root == NULL) {
                cout << "\nДерево порожнє. Неможливо знайти мінімальний елемент.\n";
            }
            else {
                cout << "\n";
                FindFirstMin(root);
                cout << "\n";
            }
            break;
        }
        case 0:
            // Очищення пам'яті перед виходом
            if (root != NULL) {
                DeleteTree(root);
                root = NULL;
            }
            cout << "Програма завершена.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }

    } while (choice != 0);

    return 0;
}