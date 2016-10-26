//
// Created by 张师睿 on 16/9/16.
// 对这个东西错综复杂的关系,gg
//

#ifndef DATASTRUCTURES_ABSBINARYTREE_HPP
#define DATASTRUCTURES_ABSBINARYTREE_HPP

template<class T>
class AbsBinaryTree {
public:
    typedef void (*VISIT_FUNC)(T *);

    virtual ~AbsBinaryTree() {}

    virtual int height() const = 0;

    virtual void preOrder(VISIT_FUNC visit) = 0;

    virtual void inOrder(VISIT_FUNC visit) = 0;

    virtual void postOrder(VISIT_FUNC visit) = 0;

    virtual void levelOrder(VISIT_FUNC visit) = 0;
};

#endif //DATASTRUCTURES_ABSBINARYTREE_HPP
