
// TrackingView.cpp: CTrackingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Tracking.h"
#endif

#include "TrackingDoc.h"
#include "TrackingView.h"
#include "Track.h"
#include "VideoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrackingView

IMPLEMENT_DYNCREATE(CTrackingView, CView)

BEGIN_MESSAGE_MAP(CTrackingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPENCV_TEST, &CTrackingView::OnOpencvTest)
	ON_COMMAND(ID_FILE_OPEN, &CTrackingView::OnFileOpen)
	ON_COMMAND(ID_TRACKER_KCF, &CTrackingView::OnTrackerKcf)
	ON_COMMAND(ID_DETECT_GSM, &CTrackingView::OnDetectGsm)
	ON_COMMAND(ID_DETECT_FRAME_DIFF, &CTrackingView::OnDetectFrameDiff)
	ON_COMMAND(ID_TRAGET_DETC_TRACKING, &CTrackingView::OnTragetDetcTracking)
	ON_COMMAND(ID_TRACKER_BOOSTING, &CTrackingView::OnTrackerBoosting)
	ON_COMMAND(ID_TRACKER_GOTURN, &CTrackingView::OnTrackerGoturn)
	ON_COMMAND(ID_TRACKER_MEDIANFLOW, &CTrackingView::OnTrackerMedianflow)
	ON_COMMAND(ID_TRACKER_MIL, &CTrackingView::OnTrackerMil)
	ON_COMMAND(ID_TRACKER_TLD, &CTrackingView::OnTrackerTld)
	ON_COMMAND(ID_TRACKER_MOSSE, &CTrackingView::OnTrackerMosse)
	ON_COMMAND(ID_TRACKER_COM, &CTrackingView::OnTrackerCom)
END_MESSAGE_MAP()

// CTrackingView 构造/析构

CTrackingView::CTrackingView()
{
	// TODO: 在此处添加构造代码

}

CTrackingView::~CTrackingView()
{
}

BOOL CTrackingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTrackingView 绘图

void CTrackingView::OnDraw(CDC* /*pDC*/)
{
	CTrackingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CTrackingView 打印

BOOL CTrackingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTrackingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTrackingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTrackingView 诊断

#ifdef _DEBUG
void CTrackingView::AssertValid() const
{
	CView::AssertValid();
}

void CTrackingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrackingDoc* CTrackingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrackingDoc)));
	return (CTrackingDoc*)m_pDocument;
}
#endif //_DEBUG


// CTrackingView 消息处理程序





void CTrackingView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CString filter = _T("mkv(*.mkv)|*.mkv|mp4(*.mp4)|*.mp4|all(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, this);

	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK){
		m_sFileName = dlg.GetPathName();  //获取文件路径名   如D:\pic\abc.bmp

		CVideoDlg videoDlg;
		videoDlg.m_vidoeUrl = m_sFileName;
		videoDlg.DoModal();
		
	}
}




void CTrackingView::OnOpencvTest()
{
	// TODO: 在此添加命令处理程序代码
	Track track;
	
	 

}



//KCF目标跟踪
void CTrackingView::OnTrackerKcf()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.TragetTracker(m_sFileName, "KCF");

}



void CTrackingView::OnTrackerBoosting()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.TragetTracker(m_sFileName, "BOOSTING");
}


void CTrackingView::OnTrackerGoturn()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.TragetTracker(m_sFileName, "BOOSTING");
}


void CTrackingView::OnTrackerMedianflow()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.TragetTracker(m_sFileName, "MEDIANFLOW");
}


void CTrackingView::OnTrackerMil()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.TragetTracker(m_sFileName, "MIL");
}


void CTrackingView::OnTrackerTld()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.TragetTracker(m_sFileName, "TLD");
}


void CTrackingView::OnTrackerMosse()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.TragetTracker(m_sFileName, "MOSSE");
}




//混合高斯模型进行目标检测
void CTrackingView::OnDetectGsm()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.GSMDetection(m_sFileName);

}

//帧间差目标检测
void CTrackingView::OnDetectFrameDiff()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.FDiffDetection(m_sFileName);
}





//最终效果 目标检测和跟踪
void CTrackingView::OnTragetDetcTracking()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.KCF(m_sFileName);

}




void CTrackingView::OnTrackerCom()
{
	// TODO: 在此添加命令处理程序代码
	if (m_sFileName.IsEmpty()) {
		AfxMessageBox(_T("请先打开视频"));
		return;
	}
	Track track;
	track.MultiTrackerCompare(m_sFileName);
}
