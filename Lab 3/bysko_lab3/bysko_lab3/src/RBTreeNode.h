#pragma once

struct RBNode {
	RBNode* p = nullptr, * l = nullptr, * r = nullptr;
	int data = 0;
	bool color = false;
};