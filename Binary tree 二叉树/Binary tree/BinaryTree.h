/*
			轻松搞定面试中的二叉树题目
	https://blog.csdn.net/luckyxiaoqiang/article/details/7518888
*/

#include <queue>
#include <list>
#include <xutility> // max

struct BinaryTreeNode
{
	int m_nValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	BinaryTreeNode()
	{
		m_nValue = 0;
		m_pLeft = NULL;
		m_pRight = NULL;
	}
	BinaryTreeNode(int nVaule)
	{
		m_nValue = nVaule;
		m_pLeft = NULL;
		m_pRight = NULL;
	}
};

// 补充二叉树的创建
////////////////////////////////////////
BinaryTreeNode* CreateBiTree(int nDepth)
{
	if (nDepth<=0)
	{
		return NULL;;
	}
	BinaryTreeNode* pNode = new BinaryTreeNode;
	pNode->m_nValue = nDepth;

	pNode->m_pLeft = CreateBiTree(nDepth-1);
	pNode->m_pRight = CreateBiTree(nDepth-1);


	return pNode;
}
////////////////////////////////////////

// 访问根节点

void Visit(BinaryTreeNode* pNode)
{
	printf("%d\n",pNode->m_nValue);
}

// 求二叉树中的节点个数

int GetNodeNum(BinaryTreeNode *pRoot)
{
	if (pRoot == NULL) // 递归出口
		return 0;
	return GetNodeNum(pRoot->m_pLeft) + GetNodeNum(pRoot->m_pRight) +1;
}

// 求二叉树的深度

int GetDepth(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)  // 递归出口
	{
		return 0;
	}
	int depthLeft = GetDepth(pRoot->m_pLeft);
	int depthRight = GetDepth(pRoot->m_pRight);
	return depthLeft > depthRight? depthLeft+1 : depthRight +1;
}

// 前序遍历

void PreOrderTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	Visit(pRoot); // 访问根节点
	PreOrderTraverse(pRoot->m_pLeft);
	PreOrderTraverse(pRoot->m_pRight);
}

// 中序遍历

void InOrderTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	InOrderTraverse(pRoot->m_pLeft);
	Visit(pRoot);
	InOrderTraverse(pRoot->m_pRight);
}

// 后续遍历

void PostOrderTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	PostOrderTraverse(pRoot->m_pLeft);
	PostOrderTraverse(pRoot->m_pRight);
	Visit(pRoot);
}

// 分层遍历二叉树

void LevelTraverse(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return;
	std::queue<BinaryTreeNode*> q;
	q.push(pRoot);
	while(!q.empty())
	{
		BinaryTreeNode* pNode = q.front();
		q.pop();
		Visit(pNode);
		if (pNode->m_pLeft != NULL)
			q.push(pNode->m_pLeft);
		if (pNode->m_pRight != NULL)
			q.push(pNode->m_pRight);
	}
}


// 将二叉查找树变为有序的双向链表

void Convert(BinaryTreeNode * pRoot,BinaryTreeNode *& pFirstNode,BinaryTreeNode*& pLastNode)
{
	BinaryTreeNode* pFirstLeft,*pLastLeft,*pFirstRight,*pLastRight;
	if (pRoot == NULL)
	{
		pFirstNode = NULL;
		pLastNode = NULL;
		return;
	}

	if (pRoot->m_pLeft == NULL)
	{
		// 如果左子树为空，对应双向有序链表的第一个节点是根节点
		pFirstNode = pRoot;
	}
	else
	{
		Convert(pRoot->m_pLeft,pFirstLeft,pLastLeft);
		pFirstNode = pFirstLeft;
		pRoot->m_pLeft = pLastLeft;
		pLastLeft->m_pRight = pRoot;
	}
	
	if (pRoot->m_pRight == NULL)
	{
		pLastNode = pRoot;
	}
	else
	{
		Convert(pRoot->m_pRight,pFirstRight,pLastRight);
		pLastNode = pLastRight;
		pRoot->m_pRight = pFirstRight;
		pFirstRight->m_pLeft  = pRoot;
	}
	return;
}

// 二叉树第K层的节点个数

int GetNodeNumKthLevel(BinaryTreeNode* pRoot,int k)
{
	if (pRoot == NULL || k <1)
		return 0;
	if ( k == 1)
		return 1;
	int numLeft = GetNodeNumKthLevel(pRoot->m_pLeft,k-1);
	int numRight = GetNodeNumKthLevel(pRoot->m_pRight,k-1);
	return numLeft + numRight;
}

// 求二叉树中叶子节点的个数

int GetLeafNodeNum(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL)
		return 1;
	int numLeft = GetLeafNodeNum(pRoot->m_pLeft);
	int numRight = GetLeafNodeNum(pRoot->m_pRight);
	return numLeft + numRight;
}

// 判断两棵二叉树是否结构相同


bool StructureCmp(BinaryTreeNode* pRoot1,BinaryTreeNode* pRoot2)
{
	if (pRoot1 == NULL && pRoot2 == NULL)
		return true;
	else if (pRoot1 == NULL || pRoot2 == NULL)
		return false;
	bool resultLeft = StructureCmp(pRoot1->m_pLeft,pRoot2->m_pRight);
	bool resultRight = StructureCmp(pRoot1->m_pRight,pRoot2->m_pRight);
	return resultLeft && resultRight;
}

// 判断二叉树是不是平衡二叉树

bool IsAVL(BinaryTreeNode* pRoot,int & height)
{
	if (pRoot == NULL)
	{
		height = 0;
		return true;
	}
	int heightLeft = 0;
	bool resultLeft = IsAVL(pRoot->m_pLeft,heightLeft);
	int heightRight = 0;
	bool resultRight = IsAVL(pRoot->m_pRight,heightRight);
	if (resultLeft && resultRight  && abs(heightLeft - heightRight) <= 1)
	{
		height = std::max(heightLeft,heightRight) + 1;
		return true;
	}
	else
	{
		height = std::max(heightLeft,heightRight) + 1;
		return false;
	}
}


// 求二叉树的镜像,在原树修改

BinaryTreeNode * Mirror(BinaryTreeNode* pRoot)
{
	if (pRoot == NULL)
		return NULL;
	BinaryTreeNode* pLeft = Mirror(pRoot->m_pLeft);
	BinaryTreeNode* pRight = Mirror(pRoot->m_pRight);

	// 交换左右子树
	pRoot->m_pLeft = pRight;
	pRoot->m_pRight = pLeft;
	return pRoot;
}

// 求二叉树中两个节点的最低公共祖先节点

bool FindNode(BinaryTreeNode* pRoot,BinaryTreeNode* pNode)
{
	if (pRoot == NULL || pNode == NULL)
		return false;
	if (pRoot == pNode)
		return true;
	bool found = FindNode(pRoot->m_pLeft,pNode);
	if (!found)
		found = FindNode(pRoot->m_pRight,pNode);
	return found;
}

BinaryTreeNode* GetLastCommonParent(BinaryTreeNode* pRoot,BinaryTreeNode* pNode1,
									BinaryTreeNode* pNode2)
{
	if (FindNode(pRoot->m_pLeft,pNode1))
	{
		if (FindNode(pRoot->m_pRight,pNode2))
			return pRoot;
		else
			return GetLastCommonParent(pRoot->m_pLeft,pNode1,pNode2);
	}
	else
	{	
		if (FindNode(pRoot->m_pLeft,pNode2))
			return pRoot;
		else
			return GetLastCommonParent(pRoot->m_pRight,pNode1,pNode2);
	}
}

// 递归解法效率很低，有很多重复的遍历，下面看一下非递归解法。
// 非递归解法：
// 先求从根节点到两个节点的路径，然后再比较对应路径的节点就行，最后一个相同的节点也就是他们在二叉树中的最低公共祖先节点

bool GetNodePath(BinaryTreeNode* pRoot,BinaryTreeNode* pNode,
				 std::list<BinaryTreeNode*> & path)
{
	if (pRoot == pNode)
	{
		path.push_back(pRoot);
		return true;
	}
	if (pRoot == NULL)
		return false;
	path.push_back(pRoot);
	bool found = false;
	found = GetNodePath(pRoot->m_pLeft,pNode,path);
	if (!found)
		found = GetNodePath(pRoot->m_pRight,pNode,path);
	if (!found)
		path.pop_back();
	return found;
}

BinaryTreeNode * GetLastCommonParent2(BinaryTreeNode * pRoot,BinaryTreeNode* pNode1,
									  BinaryTreeNode* pNode2)
{
	if (pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
		return NULL;
	std::list<BinaryTreeNode*> path1;
	bool bResult1 = GetNodePath(pRoot,pNode1,path1);
	std::list<BinaryTreeNode*> path2;
	bool bResult2 = GetNodePath(pRoot,pNode2,path2);
	if (!bResult1 || !bResult2)
		return NULL;
	BinaryTreeNode* pLast = NULL;
	std::list<BinaryTreeNode*>::const_iterator iter1 = path1.begin();
	std::list<BinaryTreeNode*>::const_iterator iter2 = path2.begin();
	while(iter1 != path1.end() && iter2 != path2.end())
	{
		if (*iter1 == *iter2)
			pLast = *iter1;
		else
			break;
		iter1++;
		iter2++;
	}
	return pLast;
}

// 求二叉树中节点的最大距离

int GetMaxDistance(BinaryTreeNode * pRoot, int & maxLeft, int & maxRight)
{
	// maxLeft, 左子树中的节点距离根节点的最远距离
	// maxRight, 右子树中的节点距离根节点的最远距离
	if(pRoot == NULL)
	{
		maxLeft = 0;
		maxRight = 0;
		return 0;
	}
	int maxLL, maxLR, maxRL, maxRR;
	int maxDistLeft, maxDistRight;
	if(pRoot->m_pLeft != NULL)
	{
		maxDistLeft = GetMaxDistance(pRoot->m_pLeft, maxLL, maxLR);
		maxLeft = std::max(maxLL, maxLR) + 1;
	}
	else
	{
		maxDistLeft = 0;
		maxLeft = 0;
	}
	if(pRoot->m_pRight != NULL)
	{
		maxDistRight = GetMaxDistance(pRoot->m_pRight, maxRL, maxRR);
		maxRight = std::max(maxRL, maxRR) + 1;
	}
	else
	{
		maxDistRight = 0;
		maxRight = 0;
	}
	return std::max(std::max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}

// 由前序遍历序列和中序遍历序列重建二叉树

BinaryTreeNode * RebuildBinaryTree(int* pPreOrder, int* pInOrder, int nodeNum)
{
	if(pPreOrder == NULL || pInOrder == NULL || nodeNum <= 0)
		return NULL;
	BinaryTreeNode * pRoot = new BinaryTreeNode;
	// 前序遍历的第一个数据就是根节点数据
	pRoot->m_nValue = pPreOrder[0];
	pRoot->m_pLeft = NULL;
	pRoot->m_pRight = NULL;
	// 查找根节点在中序遍历中的位置，中序遍历中，根节点左边为左子树，右边为右子树
	int rootPositionInOrder = -1;
	for(int i = 0; i < nodeNum; i++)
		if(pInOrder[i] == pRoot->m_nValue)
		{
			rootPositionInOrder = i;
			break;
		}
		if(rootPositionInOrder == -1)
		{
			throw std::exception("Invalid input.");
		}
		// 重建左子树
		int nodeNumLeft = rootPositionInOrder;
		int * pPreOrderLeft = pPreOrder + 1;
		int * pInOrderLeft = pInOrder;
		pRoot->m_pLeft = RebuildBinaryTree(pPreOrderLeft, pInOrderLeft, nodeNumLeft);
		// 重建右子树
		int nodeNumRight = nodeNum - nodeNumLeft - 1;
		int * pPreOrderRight = pPreOrder + 1 + nodeNumLeft;
		int * pInOrderRight = pInOrder + nodeNumLeft + 1;
		pRoot->m_pRight = RebuildBinaryTree(pPreOrderRight, pInOrderRight, nodeNumRight);
		return pRoot;
}

//判断二叉树是不是完全二叉树
bool IsCompleteBinaryTree(BinaryTreeNode * pRoot)
{
	if(pRoot == NULL)
		return false;
	std::queue<BinaryTreeNode *> q;
	q.push(pRoot);
	bool mustHaveNoChild = false;
	bool result = true;
	while(!q.empty())
	{
		BinaryTreeNode * pNode = q.front();
		q.pop();
		if(mustHaveNoChild) // 已经出现了有空子树的节点了，后面出现的必须为叶节点（左右子树都为空）
		{
			if(pNode->m_pLeft != NULL || pNode->m_pRight != NULL)
			{
				result = false;
				break;
			}
		}
		else
		{
			if(pNode->m_pLeft != NULL && pNode->m_pRight != NULL)
			{
				q.push(pNode->m_pLeft);
				q.push(pNode->m_pRight);
			}
			else if(pNode->m_pLeft != NULL && pNode->m_pRight == NULL)
			{
				mustHaveNoChild = true;
				q.push(pNode->m_pLeft);
			}
			else if(pNode->m_pLeft == NULL && pNode->m_pRight != NULL)
			{
				result = false;
				break;
			}
			else
			{
				mustHaveNoChild = true;
			}
		}
	}
	return result;
}