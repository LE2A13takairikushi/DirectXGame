#include "WorldTransform.h"

//
//void WorldTransform::UpdateMatrix()
//{
//	XMMATRIX matScale, matRot, matTrans;
//
//    matScale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
//    matRot = XMMatrixIdentity();
//    matRot *= XMMatrixRotationZ(rotation_.z);
//    matRot *= XMMatrixRotationX(rotation_.x);
//    matRot *= XMMatrixRotationY(rotation_.y);
//    matTrans = XMMatrixTranslation(translation_.x, translation_.y, translation_.z);
//
//    matWorld_ = XMMatrixIdentity(); // �ό`�����Z�b�g
//    matWorld_ *= matScale;          // ���[���h�s��ɃX�P�[�����O�𔽉f
//    matWorld_ *= matRot;            // ���[���h�s��ɉ�]�𔽉f
//    matWorld_ *= matTrans;          // ���[���h�s��ɕ��s�ړ��𔽉f
//
//    if (parent_ != nullptr)
//    {
//        matWorld_ *= parent_->matWorld_;
//    }
//
//    constMap->matWorld *= matWorld_;
//
//}