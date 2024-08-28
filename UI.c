//
// Created by Ilya Atmazhitov on 27.08.2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

void displayMenu() {
    printf("\n--- Меню ---\n");
    printf("1. Добавление нового элемента\n");
    printf("2. Удаление элемента\n");
    printf("3. Обход дерева\n");
    printf("4. Поиск элемента по ключу\n");
    printf("5. Специальный поиск элемента (поиск наименьшего ключа, большего заданного)\n");
    printf("6. Форматированный вывод дерева \"в виде дерева\"\n");
    printf("7. Графический вывод дерева с использованием Graphviz\n");
    printf("8. Загрузка дерева из текстового файла\n");
    printf("9. Удаление дерева\n");
    printf("10. Выполнение таймирования\n");
    printf("0. Выход\n");
    printf("Выберите опцию: ");
}

int Implementation() {
    struct NodeBST* root = NULL;
    int choice;
    char key[256], item[256], filename[256];

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Введите ключ: ");
                fgets(key, 256, stdin);
                key[strcspn(key, "\n")] = 0;

                if (checkDuplicate(root, key)) {
                    printf("Введите элемент: ");
                    fgets(item, 256, stdin);
                    item[strcspn(item, "\n")] = 0;
                    root = insertNode(root, key, item);

                } else {
                    root = insertNode(root, key, NULL);
                }

                printf("Элемент добавлен.\n");
                break;

            case 2:
                printf("Введите ключ для удаления: ");
                fgets(key, 256, stdin);
                key[strcspn(key, "\n")] = 0;

                root = deleteNode(root, key);
                printf("Элемент удален, если он существовал.\n");
                break;

            case 3:
                printf("Введите подстроку для фильтрации результата обхода дерева (оставьте пустым для полного обхода): ");
                fgets(key, 256, stdin);
                key[strcspn(key, "\n")] = 0;

                printf("Обход дерева с фильтрацией по подстроке \"%s\":\n", key);
                traverseTree(root, key);
                break;
            case 4:
                printf("Введите ключ для поиска: ");
                fgets(key, 256, stdin);
                key[strcspn(key, "\n")] = 0;

                searchAndPrintResults(root, key);
                break;

            case 5:
                printf("Введите ключ для специального поиска (наименьший ключ, больший заданного): ");
                fgets(key, 256, stdin);
                key[strcspn(key, "\n")] = 0;

                searchAndPrintSmallestGreaterThan(root, key);
                break;

            case 6:
                printf("Форматированный вывод дерева:\n");
                printTree(root, 0);
                break;

            case 7:
                printf("Введите имя файла для сохранения графического представления (например, tree.dot): ");
                fgets(filename, 256, stdin);
                filename[strcspn(filename, "\n")] = 0;

                visualizeTree(root, filename);
                printf("Графическое представление дерева сохранено в %s и сгенерировано в tree.png.\n", filename);
                break;

            case 8:
                printf("Введите имя текстового файла для загрузки дерева: ");
                fgets(filename, 256, stdin);
                filename[strcspn(filename, "\n")] = 0;

                loadTreeFromFile(&root, filename);
                printf("Дерево загружено из файла %s.\n", filename);
                break;

            case 9:
                deleteTree(&root);
                printf("Дерево удалено.\n");
                break;

            case 10:
                printf("Выполнение таймирования:\n");
                D_Timing(&root);
                break;

            case 0:
                printf("Выход из программы.\n");
                break;

            default:
                printf("Неверный выбор. Пожалуйста, попробуйте снова.\n");
        }
    } while (choice != 0);

    deleteTree(&root);

}