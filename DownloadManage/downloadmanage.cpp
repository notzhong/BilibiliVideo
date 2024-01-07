#include <Python.h>
#include "downloadmanage.h"
#include "ConfigValue.h"
#include "custom_define.h"
#include <QDebug>
#include <qthread.h>
#include <iostream>
#include <Windows.h>
#include <shlobj.h>

static std::string SelectFolderPath()
{
    std::string folderPath;

    BROWSEINFO browseInfo = { 0 };
    browseInfo.hwndOwner = NULL;
    browseInfo.pidlRoot = NULL;
    browseInfo.pszDisplayName = NULL;
    browseInfo.lpszTitle = L"保存路径";
    browseInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;

    LPITEMIDLIST pidl = SHBrowseForFolder(&browseInfo);
    if (pidl != NULL)
    {
        char selectedPath[MAX_PATH];
        if (SHGetPathFromIDListA(pidl, selectedPath))
        {
            folderPath = selectedPath;
        }
        CoTaskMemFree(pidl);
    }
    return folderPath;
}



DownloadManage::DownloadManage(void* pStream) :
    m_DownData(reinterpret_cast<pStreamUrl>(pStream)),
    QObject(nullptr)
{
    try
    {
        int result = PROCESS_SUCCESS;
        result = InitPyRelolver();
        if (result)
            throw result;
    }
    catch (const int result)
    {
        qDebug() << __FILE__ << Q_FUNC_INFO << __LINE__ << "error:" << result;
        exit(-2000);
    }
}

DownloadManage::~DownloadManage()
{
    Py_XDECREF(m_pFunc);
    Py_XDECREF(m_pModule);
}

int DownloadManage::InitPyRelolver() {
    // 初始化Python解释器
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    // 导入Python模块
    m_pModule = PyImport_ImportModule("meger");
    
    if (m_pModule && Py_IsInitialized()) {
        // 调用Python函数
        m_pFunc = PyObject_GetAttrString(reinterpret_cast<PyObject*>(m_pModule), "DownVideo");

        if (!m_pFunc && !PyCallable_Check(reinterpret_cast<PyObject*>(m_pFunc))) {
            Py_XDECREF(m_pFunc);
            return PROCESS_FAILED;
        }
    }
    else
    {
        // 释放资源
        Py_XDECREF(m_pModule);
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << "Py Init failed";
        qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << "load py module failed";
        return PROCESS_FAILED;
    }
    
    return PROCESS_SUCCESS;
}

int DownloadManage::ProcessDownload()
{
    PyObject* pArgs = PyTuple_New(2);
    
    std::string path = SelectFolderPath();
    printf("%s\n", path.c_str());

    PyTuple_SetItem(pArgs, 0, PyUnicode_FromString(path.c_str()));
    if (m_DownData->Base_Cookie.isEmpty())
        PyTuple_SetItem(pArgs, 1, PyUnicode_FromString(""));
    else
        PyTuple_SetItem(pArgs, 1, PyUnicode_FromString(m_DownData->Base_Cookie.toStdString().c_str()));

    PyObject* pValue = PyObject_CallObject(reinterpret_cast<PyObject*>(m_pFunc), pArgs);
    QThread::msleep(3000);

    Py_XDECREF(pArgs);

    return PROCESS_SUCCESS;
}
