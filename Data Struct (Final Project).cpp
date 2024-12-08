#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>  // For generating random numbers
#include <ctime>    // For time-based seed
using namespace std;

// Function to perform preorder traversal
void preorderTraversal(const vector<int>& arr, int index, int size) {
    if (index >= size) return;                 // Base condition: Stop if index is out of bounds
    cout << arr[index] << " ";                 // Visit the root
    preorderTraversal(arr, 2 * index + 1, size); // Visit left child
    preorderTraversal(arr, 2 * index + 2, size); // Visit right child
}

// Function to perform inorder traversal
void inorderTraversal(const vector<int>& arr, int index, int size) {
    if (index >= size) return;                 // Base condition: Stop if index is out of bounds
    inorderTraversal(arr, 2 * index + 1, size); // Visit left child
    cout << arr[index] << " ";                 // Visit the root
    inorderTraversal(arr, 2 * index + 2, size); // Visit right child
}

// Function to perform postorder traversal
void postorderTraversal(const vector<int>& arr, int index, int size) {
    if (index >= size) return;                 // Base condition: Stop if index is out of bounds
    postorderTraversal(arr, 2 * index + 1, size); // Visit left child
    postorderTraversal(arr, 2 * index + 2, size); // Visit right child
    cout << arr[index] << " ";                 // Visit the root
}

// Function to heapify a subtree rooted at index i (for Min-Heap)
void heapifyMin(vector<int>& heap, int n, int i) {
    int smallest = i;                          // Initialize the smallest as root
    int left = 2 * i + 1;                      // Left child index
    int right = 2 * i + 2;                     // Right child index

    if (left < n && heap[left] < heap[smallest]) smallest = left; // Update smallest if left child is smaller
    if (right < n && heap[right] < heap[smallest]) smallest = right; // Update smallest if right child is smaller

    if (smallest != i) {
        swap(heap[i], heap[smallest]);         // Swap with the smallest child
        heapifyMin(heap, n, smallest);        // Recursively heapify the affected subtree
    }
}

// Function to heapify a subtree rooted at index i (for Max-Heap)
void heapifyMax(vector<int>& heap, int n, int i) {
    int largest = i;                           // Initialize the largest as root
    int left = 2 * i + 1;                      // Left child index
    int right = 2 * i + 2;                     // Right child index

    if (left < n && heap[left] > heap[largest]) largest = left; // Update largest if left child is larger
    if (right < n && heap[right] > heap[largest]) largest = right; // Update largest if right child is larger

    if (largest != i) {
        swap(heap[i], heap[largest]);         // Swap with the largest child
        heapifyMax(heap, n, largest);        // Recursively heapify the affected subtree
    }
}

// Function to insert an element into the Min-Heap
void insert(vector<int>& heap, int value) {
    heap.push_back(value);                    // Add the new value at the end
    int i = heap.size() - 1;                  // Index of the new element

    while (i != 0 && heap[(i - 1) / 2] > heap[i]) { // Restore the Min-Heap property
        swap(heap[i], heap[(i - 1) / 2]);    // Swap with the parent
        i = (i - 1) / 2;                    // Move up to the parent index
    }
}

// Function to remove the smallest element (root) from the Min-Heap
void removeMin(vector<int>& heap) {
    if (heap.empty()) {                       // Check if the heap is empty
        cout << "Heap is empty! Nothing to remove." << endl;
        return;
    }
    cout << "Removing smallest guess: " << heap[0] << endl;
    heap[0] = heap.back();                    // Replace root with the last element
    heap.pop_back();                          // Remove the last element
    heapifyMin(heap, heap.size(), 0);        // Restore the Min-Heap property
}

// Function to print the current heaps and original numbers
void printHeaps(const vector<int>& original, const vector<int>& minHeap) {
    vector<int> maxHeap = original;           // Create a copy for Max-Heap
    int n = maxHeap.size();

    for (int i = n / 2 - 1; i >= 0; i--) {    // Build the Max-Heap
        heapifyMax(maxHeap, n, i);
    }

    cout << "Original inputted numbers: ";
    for (int val : original)
        cout << val << " ";                  // Print original input numbers
    cout << endl;

    cout << "Current Min-Heap: ";
    for (int val : minHeap)
        cout << val << " ";                  // Print Min-Heap
    cout << endl;

    cout << "Current Max-Heap: ";
    for (int val : maxHeap)
        cout << val << " ";                  // Print Max-Heap
    cout << endl;
}

// Function to print tree traversals of the original input
void printTraversals(const vector<int>& original) {
    cout << "\nTree Traversals of Original Numbers (Sorted):" << endl;
    vector<int> sortedInput = original;       // Sort the original numbers to simulate a BST
    sort(sortedInput.begin(), sortedInput.end());

    cout << "Preorder traversal: ";
    preorderTraversal(sortedInput, 0, sortedInput.size());
    cout << endl;

    cout << "Inorder traversal: ";
    inorderTraversal(sortedInput, 0, sortedInput.size());
    cout << endl;

    cout << "Postorder traversal: ";
    postorderTraversal(sortedInput, 0, sortedInput.size());
    cout << endl;
}

// Function to generate a random secret number within a range
int generateSecretNumber(int minRange, int maxRange) {
    return rand() % (maxRange - minRange + 1) + minRange; // Generate a random number in the range
}

// Main function containing the game logic
int main() {
    srand(time(0));                           // Seed the random number generator
    vector<int> minHeap;                      // Min-Heap for guesses
    vector<int> originalInput;                // Store original numbers
    int minRange = 1, maxRange = 100;         // Range for the secret number
    int secretNumber = generateSecretNumber(minRange, maxRange); // Generate the secret number
    int choice, guess;
    int maxGuesses = 5;                       // Maximum number of guesses
    int currentGuesses = 0;

    cout << "\033[95mWelcome to Guess the Secret Number Game!\033[0m" << endl;
    cout << "Can you guess the secret number between " << minRange << " and " << maxRange << "?" << endl;

    do {
        cout << "\n\033[95mMain Menu:\033[0m" << endl;
        cout << "1. Start guessing the secret number" << endl;
        cout << "2. Remove the smallest guess from the heap" << endl;
        cout << "3. Display the original numbers, Min-Heap, Max-Heap" << endl;
        cout << "4. Display tree traversals of original numbers" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Start guessing the secret number
                currentGuesses = 0;
                secretNumber = generateSecretNumber(minRange, maxRange);
                cout << "Start guessing! You have " << maxGuesses << " chances." << endl;
                while (currentGuesses < maxGuesses) {
                    cout << "Enter your guess: ";
                    cin >> guess;
                    originalInput.push_back(guess); // Add guess to the original input
                    insert(minHeap, guess);         // Insert into Min-Heap
                    cout << "You added the guess: " << guess << endl;
                    currentGuesses++;

                    if (guess == secretNumber) {
                        cout << "\033[95m🎉 Congratulations! You've guessed the secret number! 🎉\033[0m" << endl;
                        break;
                    } else if (guess < secretNumber) {
                        cout << "Hint: The secret number is larger than " << guess << "." << endl;
                    } else {
                        cout << "Hint: The secret number is smaller than " << guess << "." << endl;
                    }

                    if (currentGuesses >= maxGuesses && guess != secretNumber) {
                        cout << "\033[95mSorry, you've reached the maximum number of guesses! \033[0m" << endl;
                        cout << "The secret number was: " << secretNumber << endl;
                    }
                }
                break;

            case 2: // Remove the smallest guess from the Min-Heap
                removeMin(minHeap);
                break;

            case 3: // Display heaps and original numbers
                printHeaps(originalInput, minHeap);
                break;

            case 4: // Display tree traversals of original numbers
                printTraversals(originalInput);
                break;

            case 5: // Quit
                cout << "Thanks for playing! Goodbye!" << endl;
                break;

            default: // Invalid choice
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
