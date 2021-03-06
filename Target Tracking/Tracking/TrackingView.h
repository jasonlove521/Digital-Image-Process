
// TrackingView.h: CTrackingView 类的接口
//

#pragma once


class CTrackingView : public CView
{
protected: // 仅从序列化创建
	CTrackingView();
	DECLARE_DYNCREATE(CTrackingView)

// 特性
public:
	CTrackingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTrackingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//成员变量 
	CString m_sFileName;	// 图像文件名

	//成员函数

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOpencvTest();
	afx_msg void OnFileOpen();
	afx_msg void OnTrackerKcf();
	afx_msg void OnDetectGsm();
	afx_msg void OnDetectFrameDiff();
	afx_msg void OnTragetDetcTracking();
	afx_msg void OnTrackerBoosting();
	afx_msg void OnTrackerGoturn();
	afx_msg void OnTrackerMedianflow();
	afx_msg void OnTrackerMil();
	afx_msg void OnTrackerTld();
	afx_msg void OnTrackerMosse();
	afx_msg void OnTrackerCom();
};

#ifndef _DEBUG  // TrackingView.cpp 中的调试版本
inline CTrackingDoc* CTrackingView::GetDocument() const
   { return reinterpret_cast<CTrackingDoc*>(m_pDocument); }
#endif

