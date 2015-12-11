// SlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Slayer.h"
#include "SlayerDlg.h"



#pragma warning(disable:4244)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//int Puertos[10];
CString Puertos[10];
int iNumPuertos=0;

static BOOL CALLBACK callback(LPVOID lpCallbackValue,LISTPORTS_PORTINFO* lpPortInfo)
{
  /*_tprintf(TEXT("\"%s\" \"%s\"\n"),lpPortInfo->lpPortName,lpPortInfo->lpFriendlyName);*/
  //this->m_ctlComboCom.AddString(LPCSTR lPortInfo->lpPortName);
  /*if( kk == NULL )
	  kk=lpPortInfo->lpPortName;
  else*/
//	  kk+=lpPortInfo->lpPortName;
  //Puertos[iNumPuertos] = lpPortInfo->lpPortName+3;
  //strcpy((char *)Puertos[iNumPuertos],lpPortInfo->lpPortName+3);
	Puertos[iNumPuertos] = lpPortInfo->lpPortName+3;
  iNumPuertos++;
  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlayerDlg dialog

CSlayerDlg::CSlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSlayerDlg)
	m_dKD = 0.0;
	m_dKP = 0.0;
	m_dKI = 0.0;
	m_iValue = 0;
	m_strVelocidad = _T("19200");
	m_iComPort = 1;
	m_strMessage = _T("Sin Conexión");
	m_iSliderKd = 0;
	m_iSliderKi = 0;
	m_iSliderKp = 0;
	m_iVelocidad = 900;
	m_iTablaIndex = 0;
	m_iPosServo = 128;
	m_iSliderServo = 128;
	m_iCom = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSlayerDlg)
	DDX_Control(pDX, IDC_COMBO_SPEED, m_ctlComboSpeed);
	DDX_Control(pDX, IDC_COMBO_COM, m_ctlComboCom);
	DDX_Control(pDX, IDC_SLIDER_SERVO, m_CtlSliderServo);
	DDX_Control(pDX, IDC_CHECK1, m_chk1);
	DDX_Control(pDX, IDC_BUTTON_STORE, m_ctlButtonStore);
	DDX_Control(pDX, IDC_BUTTON_LOAD, m_ctlButtonLoad);
	DDX_Control(pDX, IDC_BUTTON_CONECTAR, m_ctlButtonConectar);
	DDX_Control(pDX, IDC_BUTTON_ENVIAR, m_ctlButtonEnviar);
	DDX_Control(pDX, IDC_SPIN_KP, m_CtlSpinKp);
	DDX_Control(pDX, IDC_SPIN_KD, m_CtlSpinKd);
	DDX_Control(pDX, IDC_SPIN_KI, m_CtlSpinKi);
	DDX_Control(pDX, IDC_SLIDER_KP, m_CtlSliderKp);
	DDX_Control(pDX, IDC_SLIDER_KI, m_CtlSliderKi);
	DDX_Control(pDX, IDC_SLIDER_KD, m_CtlSliderKd);
	DDX_Text(pDX, IDC_EDIT_KD, m_dKD);
	DDX_Text(pDX, IDC_EDIT_KP, m_dKP);
	DDX_Text(pDX, IDC_EDIT_KI, m_dKI);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_iValue);
	DDX_CBString(pDX, IDC_COMBO_SPEED, m_strVelocidad);
	//DDX_Text(pDX, IDC_EDIT_COM, m_iComPort);
	DDX_Text(pDX, IDC_STATIC_MSG, m_strMessage);
	DDX_Slider(pDX, IDC_SLIDER_KD, m_iSliderKd);
	DDX_Slider(pDX, IDC_SLIDER_KI, m_iSliderKi);
	DDX_Slider(pDX, IDC_SLIDER_KP, m_iSliderKp);
	DDX_Text(pDX, IDC_EDIT_VEL, m_iVelocidad);
	DDX_Text(pDX, IDC_EDIT_INDEX, m_iTablaIndex);
	DDX_Text(pDX, IDC_EDIT_SERVO, m_iPosServo);
	DDX_Slider(pDX, IDC_SLIDER_SERVO, m_iSliderServo);
	DDX_CBIndex(pDX, IDC_COMBO_COM, m_iCom);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CSlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON2, OnConnect)
	ON_BN_CLICKED(IDC_BUTTON1, OnCapturar)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_KI, OnReleasedcaptureSliderKi)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_KI, OnCustomdrawSliderKi)
	ON_EN_KILLFOCUS(IDC_EDIT_KI, OnKillfocusEditKi)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_KI, OnDeltaposSpinKi)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_KD, OnCustomdrawSliderKd)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_KP, OnCustomdrawSliderKp)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_KD, OnDeltaposSpinKd)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_KP, OnDeltaposSpinKp)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MEN_SALIR, OnMenSalir)
	ON_EN_KILLFOCUS(IDC_EDIT_KD, OnKillfocusEditKd)
	ON_EN_KILLFOCUS(IDC_EDIT_KP, OnKillfocusEditKp)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_SERVO, OnCustomdrawSliderServo)
	ON_BN_CLICKED(IDC_BUTTON_ENVIAR, OnButtonEnviar)
	ON_EN_KILLFOCUS(IDC_EDIT_SERVO, OnKillfocusEditServo)
	ON_COMMAND(ID_MEN_ABOUT, OnMenAbout)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, OnButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_STORE, OnButtonStore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSlayerDlg message handlers

BOOL CSlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    ListPorts(callback,NULL);

	for(int i=0;i<iNumPuertos;i++) {
		this->m_ctlComboCom.AddString(Puertos[i]);
		if( i==0 )
			this->m_ctlComboCom.SetCurSel(i);
	}

	
	if(i==0)
		AfxMessageBox("Error. No se ha detectado ningún puerto serie.");

   /*this->m_ctlSpinAngulo.SetBuddy(&this->m_ctlEditAngulo);*/
    this->m_ctlButtonConectar.SetShade(CShadeButtonST::SHS_SOFTBUMP);
	this->m_ctlButtonEnviar.SetShade(CShadeButtonST::SHS_SOFTBUMP);
    this->m_ctlButtonLoad.SetShade(CShadeButtonST::SHS_SOFTBUMP);
    this->m_ctlButtonStore.SetShade(CShadeButtonST::SHS_SOFTBUMP);
	this->m_CtlSpinKp.SetRange(0, 1000);
    this->m_CtlSpinKp.SetPos(0);
  	this->m_CtlSpinKd.SetRange(0, 1000);
	this->m_CtlSpinKd.SetPos(0);
	this->m_CtlSpinKi.SetRange(0, 1000);
	this->m_CtlSpinKi.SetPos(0);


	this->m_chk1.SetCheck(FALSE);
//this->m_chk1.SetLedColor(RGB(255, 0, 0), RGB(128, 0, 0));


	this->m_CtlSliderServo.SetRange(0,255);	
   this->m_CtlSliderServo.SetPageSize(10);	
	this->m_CtlSliderServo.SetPos(128);   
/*   this->m_CtlSliderServo.SetZero(270);
   this->m_CtlSliderServo.SetKnobRadius(5);*/
   //this->m_CtlSliderServoSetRange(-179, 180, FALSE);

   this->m_CtlSliderKp.SetRange(0,1000);	
   this->m_CtlSliderKp.SetPageSize(50);	
   this->m_CtlSliderKd.SetRange(0,1000);	
   this->m_CtlSliderKd.SetPageSize(50);	
   this->m_CtlSliderKi.SetRange(0,1000);	
   this->m_CtlSliderKi.SetPageSize(50);	


   AfxGetMainWnd()->SetWindowText(_T("Slayer Control Center"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSlayerDlg::OnLoad() 
{
	// TODO: Add your control notification handler code here
	
}

void CSlayerDlg::OnStore() 
{
	// TODO: Add your control notification handler code here
	
}

void CSlayerDlg::OnConnect() 
{

	

/*	if(this->m_chk1.GetCheck())
		this->m_chk1.SetCheck(FALSE);
	else
		this->m_chk1.SetCheck(TRUE);*/
	// TODO: Add your control notification handler code here
	
	//else

	UpdateData(TRUE);
	if( this->m_pSerie.IsOpened() == TRUE ) {
		this->m_pSerie.Close();
		//if( this->m_strMessage.Compare((LPCSTR)"Sin conexión") )
		this->m_ctlButtonConectar.SetWindowText("Conectar");
		this->m_chk1.SetCheck(FALSE);
		this->m_strMessage = "Sin conexión";
		UpdateData(FALSE);
		return;
	
	}
			UpdateData(FALSE);
   //if( this->m_pSerie.Open(this->m_iComPort,_ttoi(this->m_strVelocidad)) == FALSE ) {
	CString strCom;
	this->m_ctlComboCom.GetLBText(this->m_iCom,strCom);
	if( this->m_pSerie.Open(_ttoi(strCom),_ttoi(this->m_strVelocidad)) == FALSE ) {
		AfxMessageBox("Error al abrir el puerto serie.");
		this->m_chk1.SetCheck(FALSE);
		m_strMessage = "Sin conexión";
      
   }
	else {
		//CString strMess;
		/*sprintf(m_strMessage.GetBuffer(0),"COM%d a %s bps.",this->m_iComPort,this->m_strVelocidad);
		UpdateData(TRUE);*/
      m_strMessage.Format("COM%d a %s bps.",_ttoi(strCom),this->m_strVelocidad);
      this->m_chk1.SetCheck(TRUE);
      this->m_ctlButtonConectar.SetWindowText("Desconectar");
		//AfxMessageBox(strMess);
	}
	
   UpdateData(FALSE);
	
}

void CSlayerDlg::OnCancel() {

   this->m_pSerie.Close();
   CDialog::OnCancel();
}
void CSlayerDlg::OnOK() {

   UpdateData(TRUE);
   this->m_CtlSliderServo.SetPos(this->m_iPosServo);
   this->m_CtlSliderKi.SetPos(1000-this->m_dKI*1000);
   this->m_CtlSliderKd.SetPos(1000-this->m_dKD*1000);
   this->m_CtlSliderKp.SetPos(1000-this->m_dKP*1000);
   UpdateData(FALSE);


   //UpdateData(TRUE);
}
void CSlayerDlg::OnCapturar() 
{
	// TODO: Add your control notification handler code here
	//this->m_dKD=0.1; UpdateData(FALSE);
	UpdateData(TRUE);
	//AfxMessageBox(this->m_iComPort);
	//AfxMessageBox(_T(this->m_iComPort));
	
}

void CSlayerDlg::OnReleasedcaptureSliderKi(NMHDR* pNMHDR, LRESULT* pResult) 
{
   //AfxMessageBox("Toooda la historia");	
 /*  CString kk;
   UpdateData(TRUE);
   kk.Format("%d",this->m_iSliderKi);
   AfxMessageBox(kk);*/
	*pResult = 0;
}

void CSlayerDlg::OnCustomdrawSliderKp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
   this->m_dKP = (1000-this->m_iSliderKp)/1000.0;	
   UpdateData(FALSE);
	*pResult = 0;
}

void CSlayerDlg::OnCustomdrawSliderKd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
   this->m_dKD = (1000-this->m_iSliderKd)/1000.0;	
   UpdateData(FALSE);
	*pResult = 0;
}


void CSlayerDlg::OnCustomdrawSliderKi(NMHDR* pNMHDR, LRESULT* pResult) 
{
   UpdateData(TRUE);
   this->m_dKI = (1000-this->m_iSliderKi)/1000.0;	
   UpdateData(FALSE);
   *pResult = 0;
}


void CSlayerDlg::OnKillfocusEditKi() 
{
	// TODO: Add your control notification handler code here
   UpdateData(TRUE);
	this->m_CtlSliderKi.SetPos(1000-this->m_dKI*1000);
   UpdateData(FALSE);
	
}
void CSlayerDlg::OnKillfocusEditKd() 
{
   UpdateData(TRUE);
	this->m_CtlSliderKd.SetPos(1000-this->m_dKD*1000);
   UpdateData(FALSE);

	
}

void CSlayerDlg::OnKillfocusEditKp() 
{
   UpdateData(TRUE);
	this->m_CtlSliderKp.SetPos(1000-this->m_dKP*1000);
   UpdateData(FALSE);

	
}

void CSlayerDlg::OnDeltaposSpinKi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	UpdateData(TRUE);
   if( (this->m_dKI + pNMUpDown->iDelta/1000.0) > 1.0 )
      this->m_dKI = 1.0;
   else {
      if( (this->m_dKI + pNMUpDown->iDelta/1000.0) < 0.0 )
         this->m_dKI = 0.0;
      else
         this->m_dKI += pNMUpDown->iDelta/1000.0;
   }
   
   this->m_CtlSliderKi.SetPos(1000-this->m_dKI*1000);
   UpdateData(FALSE);
	*pResult = 0;
}


void CSlayerDlg::OnDeltaposSpinKd(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	if( (this->m_dKD + pNMUpDown->iDelta/1000.0) > 1.0 )
      this->m_dKD = 1.0;
   else {
      if( (this->m_dKD + pNMUpDown->iDelta/1000.0) < 0.0 )
         this->m_dKD = 0.0;
      else
         this->m_dKD += pNMUpDown->iDelta/1000.0;
   }
   
   this->m_CtlSliderKd.SetPos(1000-this->m_dKD*1000);
   
   UpdateData(FALSE);
	*pResult = 0;
}

void CSlayerDlg::OnDeltaposSpinKp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	UpdateData(TRUE);
	if( (this->m_dKP + pNMUpDown->iDelta/1000.0) > 1.0 )
      this->m_dKP = 1.0;
   else {
      if( (this->m_dKP + pNMUpDown->iDelta/1000.0) < 0.0 )
         this->m_dKP = 0.0;
      else
         this->m_dKP += pNMUpDown->iDelta/1000.0;
   }
   
   this->m_CtlSliderKp.SetPos(1000-this->m_dKP*1000);
   UpdateData(FALSE);
	
	*pResult = 0;
}

void CSlayerDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
   PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));	
   CDialog::OnLButtonDown(nFlags, point);
}

void CSlayerDlg::OnMenSalir() 
{
   OnCancel();	
}


void CSlayerDlg::OnCustomdrawSliderServo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
   UpdateData(TRUE);
   this->m_iPosServo = this->m_iSliderServo;	
   UpdateData(FALSE);
   *pResult = 0;

}

void CSlayerDlg::OnButtonEnviar() 
{

	unsigned char cabecera;
	char trama[10];
	bool flag=TRUE;
	char* lpBuffer = new char[10];
	int nBytesRead;
	
	if( this->m_pSerie.IsOpened() == FALSE ) {
		AfxMessageBox(_T("El puerto serie no está abierto"));
		return;
	}

	UpdateData(TRUE);

	/**************************************************/
	cabecera=SSERVO;
	sprintf(trama,"%d\r",SSERVO);
	//sprintf(trama,"65\r");
	this->m_pSerie.SendData((const char *)trama,strlen(trama));
	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SSERVO. No se obtiene respuesta");
		return;
	}
	if( lpBuffer[0] == SSERVO ) {
	
		sprintf(trama,"%d\r",this->m_iPosServo);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		}
	else {
		AfxMessageBox("Respuesta errónea");
	}
	Sleep(100);	
	/**************************************************/
//return;

	flag=TRUE;
	cabecera=SVEL;
	sprintf(trama,"%d\r",SVEL);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));
	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SVEL. No se obtiene respuesta");
		return;
	}
	if( lpBuffer[0] == SVEL ) {
	
		sprintf(trama,"%d\r",this->m_iVelocidad);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		}
	else {
		AfxMessageBox("Respuesta errónea");
	}
	Sleep(100);
	/**************************************************/
	//return;
	
	flag=TRUE;
	cabecera=SKP;
	sprintf(trama,"%d\r",SKP);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));
	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SKP. No se obtiene respuesta");
		return;
	}
	if( lpBuffer[0] == SKP ) {
	
		sprintf(trama,"%.3f\r",this->m_dKP);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		}
	Sleep(100);

	/**************************************************/
	flag=TRUE;
	cabecera=SKD;
	sprintf(trama,"%d\r",SKD);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));
	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SKD. No se obtiene respuesta");
		return;
	}
	
	//AfxMessageBox(lpBuffer[0]);
	if( lpBuffer[0] == SKD ) {
		
		sprintf(trama,"%.3f\r",this->m_dKD);
		//sprintf(trama,"0.1\r");
		//AfxMessageBox(trama);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		//this->m_pSerie.SendData((const char *)trama,4);
		}
	else {
		AfxMessageBox("Respuesta errónea");
	}
	Sleep(100);
	/**************************************************/

	flag=TRUE;
	cabecera=SKI;
	sprintf(trama,"%d\r",SKI);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));
	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SKI. No se obtiene respuesta");
		return;
	}
	if( lpBuffer[0] == SKI ) {
	
		sprintf(trama,"%.3f\r",this->m_dKI);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		}
	else {
		AfxMessageBox("Respuesta errónea");
	}
	Sleep(100);
	
/**************************************************/
	
/*	while(pSerie->ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(10);
		flag=FALSE;
	}*/

	/*cabecera=SKP;
	this->m_pSerie.SendData((const char *)&cabecera,1);
	sprintf(trama,"%.3lf\r\n",this->m_dKP);
	//AfxMessageBox(trama);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));

	cabecera=SKD;
	this->m_pSerie.SendData((const char *)&cabecera,1);
	sprintf(trama,"%.3lf\r\n",this->m_dKD);
	//AfxMessageBox(trama);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));

	cabecera=SKI;
	this->m_pSerie.SendData((const char *)&cabecera,1);
	sprintf(trama,"%.3lf\r\n",this->m_dKI);
	//AfxMessageBox(trama);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));

	cabecera=SVEL;
	this->m_pSerie.SendData((const char *)&cabecera,1);
	sprintf(trama,"%d\r\n",this->m_iVelocidad);
	//AfxMessageBox(trama);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));*/
	
	//AfxMessageBox("enviao");
	delete []lpBuffer;
}

void CSlayerDlg::OnKillfocusEditServo() 
{
	// TODO: Add your control notification handler code here
   UpdateData(TRUE);
   this->m_CtlSliderServo.SetPos(this->m_iPosServo);
   UpdateData(FALSE);
}

void CSlayerDlg::OnMenAbout() 
{
   CAboutDlg dlg;
   dlg.DoModal();
}





void CSlayerDlg::OnButtonLoad() 
{
	


	unsigned char cabecera;
	char trama[10];
	bool flag=TRUE;
	char* lpBuffer = new char[10];
	int nBytesRead;

		if( this->m_pSerie.IsOpened() == FALSE ) {
		AfxMessageBox(_T("El puerto serie no está abierto"));
		return;
	}

	UpdateData(TRUE);
	flag=TRUE;
	cabecera=SLOAD;
	sprintf(trama,"%d\r",SLOAD);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));
	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SLOAD. No se obtiene respuesta");
		return;
	}
	if( lpBuffer[0] == SLOAD ) {
	
		sprintf(trama,"%d\r",this->m_iTablaIndex);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		}
	else {
		AfxMessageBox("Respuesta errónea");
		return;
	}

	flag=TRUE;

	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SLOAD. No se obtiene respuesta");
		return;
	}

	this->m_iValue = lpBuffer[0];
	UpdateData(FALSE);

	
}


void CSlayerDlg::OnButtonStore() 
{


	unsigned char cabecera;
	char trama[10];
	bool flag=TRUE;
	char* lpBuffer = new char[10];
	int nBytesRead;



	if( this->m_pSerie.IsOpened() == FALSE ) {
		AfxMessageBox(_T("El puerto serie no está abierto"));
		return;
	}


	UpdateData(TRUE);
	flag=TRUE;
	cabecera=SSTORE;
	sprintf(trama,"%d\r",SSTORE);
	this->m_pSerie.SendData((const char *)trama,strlen(trama));
	while(this->m_pSerie.ReadDataWaiting() == 0  && flag == TRUE) {
		Sleep(100);
		flag=FALSE;
		}
		
	nBytesRead = this->m_pSerie.ReadData(lpBuffer, 10);
	if( nBytesRead == 0 ) {
		AfxMessageBox("SSTORE. No se obtiene respuesta");
		return;
	}
	if( lpBuffer[0] == SSTORE ) {
	
		sprintf(trama,"%d\r",this->m_iTablaIndex);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		Sleep(100);
		sprintf(trama,"%d\r",this->m_iValue);
		this->m_pSerie.SendData((const char *)trama,strlen(trama));
		}
	else {
		AfxMessageBox("Respuesta errónea");
	}
	
	
}
