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
//    matWorld_ = XMMatrixIdentity(); // 変形をリセット
//    matWorld_ *= matScale;          // ワールド行列にスケーリングを反映
//    matWorld_ *= matRot;            // ワールド行列に回転を反映
//    matWorld_ *= matTrans;          // ワールド行列に平行移動を反映
//
//    if (parent_ != nullptr)
//    {
//        matWorld_ *= parent_->matWorld_;
//    }
//
//    constMap->matWorld *= matWorld_;
//
//}