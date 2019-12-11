from binary_search_tree import *

bst = BinarySearchTree(10)
input_key_list = [3, 15, 6, 13, 17, 5, 12, 14, 16, 18]
bst.insert_key_list(input_key_list)
bst_list = bst.list_inorder()
print("BST List: {}\n".format(bst_list))
print("Expected output BST List: {}\n\n".format([3, 5, 6, 10, 12, 13, 14, 15, 16, 17, 18]))

bst_minimum = bst.minimum().key
bst_maximum = bst.maximum().key
print("BST min and max: {}, {}\n".format(bst_minimum, bst_maximum))
print("Expected BST min and max: {}, {}\n\n".format(3, 18))

bst_search = bst.search_key(6)
bst_prede_key = bst.predecessor(bst_search).key
bst_suc_key = bst.successor(bst_search).key
print("BST prede- and successor of key 15: {}, {}\n".format(bst_prede_key, bst_suc_key))
print("Expected BST prede- and successor: {}, {}\n\n".format(5, 10))

bst.delete_key(10)
bst.delete_key(17)
bst.delete_key(18)
bst.delete_key(3)
bst.delete_key(12)
bst_list_after_del = bst.list_inorder()
print("BST List after deletions: {}\n".format(bst_list_after_del))
print("Expected output BST List: {}\n\n".format([5, 6, 13, 14, 15, 16]))
