#include "qmlhttprequest.hpp"
#include "request.hpp"

namespace qhr {

/*!
 * \class QmlHttpRequest
 * \brief QmlHttpRequest class reponsible for creating a new \ref Request. It
 * can be used in QML to create a new \ref Request
 */

/*!
 * \brief Returns the singleton instance of \ref QmlHttpRequest
 * \return
 */
QmlHttpRequest& QmlHttpRequest::singleton()
{
    static QmlHttpRequest qhr;
    return qhr;
}

QmlHttpRequest::QmlHttpRequest(QObject* parent)
    : QObject { parent },
      mNam(new QNetworkAccessManager())
{
    setRedirectPolicy(RedirectPolicy::NoLessSafeRedirectPolicy);
}

/*!
 * \brief QmlHttpRequest::newRequest() Creates a new \ref Request object that
 * can be used to make HTTP request.
 * \note This \ref Request object should be deleted when done with using \ref
 * Request::destroy() from QML or \a\b Request::deleteLater()
 * \return A \ref Request
 */
Request* QmlHttpRequest::newRequest()
{
    return new Request(mNam, mNam->transferTimeout(), this);
}

/*!
 * \brief QmlHttpRequest::setDefaultTimeout() Set the default timeout for all
 * requests created using this class. Zero means no timeout.
 * \param timeout Time out in milliseconds
 */
void QmlHttpRequest::setDefaultTimeout(int timeout)
{
    mNam->setTransferTimeout(timeout);
}

/*!
 * \brief QmlHttpRequest::setRedirectPolicy() Set redirect policy.
 * \see \a\b QNetworkRequest::RedirectPolicy
 * \param rp
 */
void QmlHttpRequest::setRedirectPolicy(RedirectPolicy rp)
{
    mNam->setRedirectPolicy(QNetworkRequest::RedirectPolicy(rp));
}

QmlHttpRequest::RedirectPolicy QmlHttpRequest::redirectPolicy() const
{
    return RedirectPolicy(mNam->redirectPolicy());
}

#if QT_VERSION_MAJOR == 5
void registerQmlHttpRequestMethods()
{
    qmlRegisterSingletonInstance(
        "qmlhttprequest", 1, 0, "QmlHttpRequest", &QmlHttpRequest::singleton());
    qmlRegisterUncreatableType<qhr::Request>("qmlhttprequest", 1, 0,
        "Request", "Request can not be created from QML");
}

Q_COREAPP_STARTUP_FUNCTION(registerQmlHttpRequestMethods)
#endif

}
