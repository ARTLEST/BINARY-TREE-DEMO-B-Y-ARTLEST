/*
 * Professional Binary Tree Implementation and Analysis
 * Code hints and optimizations by artlest
 * 
 * This implementation demonstrates fundamental binary tree operations
 * using professional C++ development practices and terminology.
 * Designed for cross-platform compatibility and educational demonstration.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

// Node structure definition for binary tree implementation
struct TreeNode {
    int data_payload;           // The integer value stored in this node
    TreeNode* left_child_ptr;   // Pointer to the left subtree node
    TreeNode* right_child_ptr;  // Pointer to the right subtree node
    
    // Constructor initializes the node with specified data value
    TreeNode(int value) : data_payload(value), left_child_ptr(nullptr), right_child_ptr(nullptr) {}
};

// Function declarations for binary tree operations
TreeNode* insert_node_iterative(TreeNode* root_ptr, int insertion_value);
void perform_inorder_traversal(TreeNode* current_node, std::vector<int>& traversal_results);
void perform_preorder_traversal(TreeNode* current_node, std::vector<int>& traversal_results);
void perform_postorder_traversal(TreeNode* current_node, std::vector<int>& traversal_results);
int calculate_tree_height(TreeNode* current_node);
int count_total_nodes(TreeNode* current_node);
bool search_node_value(TreeNode* current_node, int target_value);
void display_progress_indicator(int current_step, int total_steps);
void display_traversal_results(const std::vector<int>& results, const std::string& traversal_type);
void perform_statistical_analysis(const std::vector<int>& dataset);
void deallocate_tree_memory(TreeNode* current_node);

int main() {
    // Program initialization and header display
    std::cout << "========================================\n";
    std::cout << "   Binary Tree Professional Demo\n";
    std::cout << "   Advanced Data Structure Analysis\n";
    std::cout << "========================================\n\n";
    
    // Initialize root pointer for binary search tree
    TreeNode* tree_root_ptr = nullptr;
    
    // Predefined dataset for deterministic execution and testing
    std::vector<int> input_dataset = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    int total_operations = input_dataset.size();
    
    std::cout << "Phase 1: Tree Construction and Node Insertion\n";
    std::cout << "---------------------------------------------\n";
    
    // Iterative insertion process with progress tracking
    for (int operation_index = 0; operation_index < total_operations; operation_index++) {
        int current_value = input_dataset[operation_index];
        
        // Display current insertion operation
        std::cout << "Inserting node with value: " << std::setw(3) << current_value << " ";
        
        // Perform node insertion into binary search tree
        tree_root_ptr = insert_node_iterative(tree_root_ptr, current_value);
        
        // Display progress indicator for current operation
        display_progress_indicator(operation_index + 1, total_operations);
        std::cout << std::endl;
    }
    
    std::cout << "\nPhase 2: Tree Structure Analysis\n";
    std::cout << "--------------------------------\n";
    
    // Calculate and display tree metrics
    int tree_height = calculate_tree_height(tree_root_ptr);
    int node_count = count_total_nodes(tree_root_ptr);
    
    std::cout << "Tree Height (Maximum Depth): " << tree_height << std::endl;
    std::cout << "Total Node Count: " << node_count << std::endl;
    std::cout << "Tree Balance Factor: " << std::fixed << std::setprecision(2) 
              << (double)node_count / (double)tree_height << std::endl;
    
    std::cout << "\nPhase 3: Tree Traversal Operations\n";
    std::cout << "----------------------------------\n";
    
    // Perform inorder traversal and collect results
    std::vector<int> inorder_results;
    perform_inorder_traversal(tree_root_ptr, inorder_results);
    display_traversal_results(inorder_results, "In-Order");
    
    // Perform preorder traversal and collect results
    std::vector<int> preorder_results;
    perform_preorder_traversal(tree_root_ptr, preorder_results);
    display_traversal_results(preorder_results, "Pre-Order");
    
    // Perform postorder traversal and collect results
    std::vector<int> postorder_results;
    perform_postorder_traversal(tree_root_ptr, postorder_results);
    display_traversal_results(postorder_results, "Post-Order");
    
    std::cout << "\nPhase 4: Search Operations and Validation\n";
    std::cout << "----------------------------------------\n";
    
    // Test search functionality with various values
    std::vector<int> search_targets = {25, 75, 100, 1, 50};
    
    for (int target_value : search_targets) {
        bool search_result = search_node_value(tree_root_ptr, target_value);
        std::cout << "Search for value " << std::setw(3) << target_value << ": " 
                  << (search_result ? "FOUND" : "NOT FOUND") << std::endl;
    }
    
    std::cout << "\nPhase 5: Statistical Analysis\n";
    std::cout << "----------------------------\n";
    
    // Perform comprehensive statistical analysis on the dataset
    perform_statistical_analysis(inorder_results);
    
    std::cout << "\nPhase 6: Memory Management\n";
    std::cout << "-------------------------\n";
    
    // Deallocate all dynamically allocated memory
    deallocate_tree_memory(tree_root_ptr);
    std::cout << "Tree memory successfully deallocated.\n";
    
    std::cout << "\n========================================\n";
    std::cout << "   Binary Tree Demo Completed Successfully\n";
    std::cout << "   All operations executed without errors\n";
    std::cout << "========================================\n";
    
    return 0;
}

// Iterative insertion function for binary search tree construction
TreeNode* insert_node_iterative(TreeNode* root_ptr, int insertion_value) {
    // Create new node with specified value
    TreeNode* new_node_ptr = new TreeNode(insertion_value);
    
    // Handle case where tree is empty (first insertion)
    if (root_ptr == nullptr) {
        return new_node_ptr;
    }
    
    // Initialize traversal pointers for iterative insertion
    TreeNode* current_node_ptr = root_ptr;
    TreeNode* parent_node_ptr = nullptr;
    
    // Traverse tree to find appropriate insertion position
    while (current_node_ptr != nullptr) {
        parent_node_ptr = current_node_ptr;
        
        // Navigate left subtree for smaller values
        if (insertion_value < current_node_ptr->data_payload) {
            current_node_ptr = current_node_ptr->left_child_ptr;
        }
        // Navigate right subtree for larger values
        else if (insertion_value > current_node_ptr->data_payload) {
            current_node_ptr = current_node_ptr->right_child_ptr;
        }
        // Handle duplicate values (ignore insertion)
        else {
            delete new_node_ptr;
            return root_ptr;
        }
    }
    
    // Insert new node at appropriate position
    if (insertion_value < parent_node_ptr->data_payload) {
        parent_node_ptr->left_child_ptr = new_node_ptr;
    } else {
        parent_node_ptr->right_child_ptr = new_node_ptr;
    }
    
    return root_ptr;
}

// Recursive inorder traversal implementation (Left-Root-Right)
void perform_inorder_traversal(TreeNode* current_node, std::vector<int>& traversal_results) {
    // Base case: null node encountered
    if (current_node == nullptr) {
        return;
    }
    
    // Recursively process left subtree
    perform_inorder_traversal(current_node->left_child_ptr, traversal_results);
    
    // Process current node data
    traversal_results.push_back(current_node->data_payload);
    
    // Recursively process right subtree
    perform_inorder_traversal(current_node->right_child_ptr, traversal_results);
}

// Recursive preorder traversal implementation (Root-Left-Right)
void perform_preorder_traversal(TreeNode* current_node, std::vector<int>& traversal_results) {
    // Base case: null node encountered
    if (current_node == nullptr) {
        return;
    }
    
    // Process current node data first
    traversal_results.push_back(current_node->data_payload);
    
    // Recursively process left subtree
    perform_preorder_traversal(current_node->left_child_ptr, traversal_results);
    
    // Recursively process right subtree
    perform_preorder_traversal(current_node->right_child_ptr, traversal_results);
}

// Recursive postorder traversal implementation (Left-Right-Root)
void perform_postorder_traversal(TreeNode* current_node, std::vector<int>& traversal_results) {
    // Base case: null node encountered
    if (current_node == nullptr) {
        return;
    }
    
    // Recursively process left subtree
    perform_postorder_traversal(current_node->left_child_ptr, traversal_results);
    
    // Recursively process right subtree
    perform_postorder_traversal(current_node->right_child_ptr, traversal_results);
    
    // Process current node data last
    traversal_results.push_back(current_node->data_payload);
}

// Calculate maximum height of binary tree using recursive approach
int calculate_tree_height(TreeNode* current_node) {
    // Base case: empty subtree has height 0
    if (current_node == nullptr) {
        return 0;
    }
    
    // Calculate height of left subtree
    int left_subtree_height = calculate_tree_height(current_node->left_child_ptr);
    
    // Calculate height of right subtree
    int right_subtree_height = calculate_tree_height(current_node->right_child_ptr);
    
    // Return maximum height plus current level
    return 1 + std::max(left_subtree_height, right_subtree_height);
}

// Count total number of nodes in binary tree recursively
int count_total_nodes(TreeNode* current_node) {
    // Base case: null node contributes 0 to count
    if (current_node == nullptr) {
        return 0;
    }
    
    // Return count of current node plus left and right subtrees
    return 1 + count_total_nodes(current_node->left_child_ptr) + count_total_nodes(current_node->right_child_ptr);
}

// Search for specific value in binary search tree
bool search_node_value(TreeNode* current_node, int target_value) {
    // Base case: reached null node (value not found)
    if (current_node == nullptr) {
        return false;
    }
    
    // Target value found at current node
    if (current_node->data_payload == target_value) {
        return true;
    }
    
    // Search left subtree for smaller target value
    if (target_value < current_node->data_payload) {
        return search_node_value(current_node->left_child_ptr, target_value);
    }
    // Search right subtree for larger target value
    else {
        return search_node_value(current_node->right_child_ptr, target_value);
    }
}

// Display visual progress indicator for operations
void display_progress_indicator(int current_step, int total_steps) {
    const int progress_bar_width = 20;
    int filled_segments = (current_step * progress_bar_width) / total_steps;
    
    std::cout << "[";
    for (int segment_index = 0; segment_index < progress_bar_width; segment_index++) {
        if (segment_index < filled_segments) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << std::setw(3) << (current_step * 100) / total_steps << "%";
}

// Display formatted traversal results with professional presentation
void display_traversal_results(const std::vector<int>& results, const std::string& traversal_type) {
    std::cout << traversal_type << " Traversal: ";
    
    for (size_t element_index = 0; element_index < results.size(); element_index++) {
        std::cout << results[element_index];
        if (element_index < results.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

// Perform comprehensive statistical analysis on dataset
void perform_statistical_analysis(const std::vector<int>& dataset) {
    if (dataset.empty()) {
        std::cout << "No data available for statistical analysis.\n";
        return;
    }
    
    // Calculate sum and mean value
    int sum_total = 0;
    for (int value : dataset) {
        sum_total += value;
    }
    double mean_value = static_cast<double>(sum_total) / dataset.size();
    
    // Find minimum and maximum values
    int minimum_value = *std::min_element(dataset.begin(), dataset.end());
    int maximum_value = *std::max_element(dataset.begin(), dataset.end());
    
    // Calculate range and median
    int value_range = maximum_value - minimum_value;
    std::vector<int> sorted_dataset = dataset;
    std::sort(sorted_dataset.begin(), sorted_dataset.end());
    double median_value = (sorted_dataset.size() % 2 == 0) ?
        (sorted_dataset[sorted_dataset.size()/2 - 1] + sorted_dataset[sorted_dataset.size()/2]) / 2.0 :
        sorted_dataset[sorted_dataset.size()/2];
    
    // Display statistical metrics
    std::cout << "Dataset Size: " << dataset.size() << " elements\n";
    std::cout << "Sum Total: " << sum_total << std::endl;
    std::cout << "Mean Value: " << std::fixed << std::setprecision(2) << mean_value << std::endl;
    std::cout << "Median Value: " << std::fixed << std::setprecision(2) << median_value << std::endl;
    std::cout << "Minimum Value: " << minimum_value << std::endl;
    std::cout << "Maximum Value: " << maximum_value << std::endl;
    std::cout << "Value Range: " << value_range << std::endl;
}

// Recursive memory deallocation for entire tree structure
void deallocate_tree_memory(TreeNode* current_node) {
    // Base case: null node requires no deallocation
    if (current_node == nullptr) {
        return;
    }
    
    // Recursively deallocate left subtree
    deallocate_tree_memory(current_node->left_child_ptr);
    
    // Recursively deallocate right subtree
    deallocate_tree_memory(current_node->right_child_ptr);
    
    // Deallocate current node memory
    delete current_node;
}