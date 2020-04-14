#include "HHttpTest.h"
#include "HHttpClient.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

void HHttpTest::run()
{
    // 在代码块里执行网络访问，是为了测试 HHttpClient 对象在被析构后，网络访问的回调函数仍然能正常执行
    {
        QString url("http://localhost:8080/api/rest");

        // [1] GET 请求无参数
        HHttpClient(url).success([](const QString &response) {
            qDebug().noquote() << response;
        }).get();

        // [2] GET 请求有参数，有自定义 header，有失败的回调函数
        // 提示: 多个参数也可以传入 map: HHttpClient(url).params({{"name", "诸葛亮"}, {"attackDamage", "99"}}).get(...);
        HHttpClient(url).debug(true).param("name", "诸葛亮").param("value", 99).header("token", "md5sum").success([](const QString &response) {
            qDebug().noquote() << response;
        }).fail([](const QString &error, int errorCode) {
            qDebug().noquote() << error << errorCode;
        }).get();

        // [3] POST 请求，使用 param 添加参数，请求的参数使用 Form 格式
        HHttpClient(url).debug(true).param("name", "卧龙").param("value", 99).success([](const QString &response) {
            qDebug().noquote() << response;
        }).post();

        // [4] PUT 请求，使用 json 添加参数，请求的参数使用 Json 格式
        HHttpClient(url).debug(true).json(R"({"name": "孔明"})").success([](const QString &response) {
            qDebug().noquote() << response;
        }).put();

        // [5] DELETE 请求
        HHttpClient(url).debug(true).success([](const QString &response) {
            qDebug().noquote() << response;
        }).remove();
    }

    {
        // [6] 下载: 保存到文件
        HHttpClient("http://qtdebug.com/img/dog.png").debug(true).success([](const QString &response) {
            qDebug().noquote() << response;
        }).download("/Users/Biao/Desktop/dog-1.png");
    }

    {
        // 上传的同时能够传递参数
        // [7] 上传一个文件
        HHttpClient("http://localhost:8080/api/upload").debug(true).upload(QString("/Users/Biao/Pictures/ade.jpg"));

        // [8] 上传多个文件
        HHttpClient("http://localhost:8080/api/uploads").debug(true).param("name", "Biao").success([](const QString &response) {
            qDebug().noquote() << response;
        }).upload({ "/Users/Biao/Pictures/ade.jpg", "/Users/Biao/Pictures/avatar.jpg" });
    }

    {
        // [9] 共享 QNetworkAccessManager
        // 每创建一个 QNetworkAccessManager 对象都会创建一个线程，当频繁的访问网络时，为了节省线程资源，调用 manager()
        // 使用共享的 QNetworkAccessManager，它不会被 HHttpClient 删除，需要我们自己不用的时候删除它。
        // 如果下面的代码不传入 QNetworkAccessManager，从任务管理器里可以看到创建了几千个线程。
        auto manager = new QNetworkAccessManager();
        for (int i = 0; i < 5000; ++i)
        {
            HHttpClient("http://localhost:8080/api/rest").manager(manager).success([=](const QString &response) {
                qDebug().noquote() << response << ", " << i;
            }).get();
        }
    }

}

// 服务器端处理请求的代码
// 这里的服务器端处理请求的代码使用了 SpringMVC 实现，作为参考，可以使用其他语言实现，例如 PHP，C#。
//import com.xtuer.bean.Result;
//import org.springframework.stereotype.Controller;
//import org.springframework.web.bind.annotation.*;
//import org.springframework.web.multipart.MultipartFile;

//import java.util.Map;

//@Controller
//public class Controller {
//    /**
//     * http://localhost:8080/api/rest
//     */
//    @GetMapping("/api/rest")
//    @ResponseBody
//    public Object restGet(@RequestParam(required = false, defaultValue = "Alice") String name,
//                          @RequestParam(required = false, defaultValue = "0") int value) {
//        Map<String, String> map = new HashMap<>();
//        map.put("name", name);
//        map.put("attackDamage", value + "");
//        map.put("method", "GET");

//        return map;
//    }

//    /**
//     * http://localhost:8080/api/rest
//     */
//    @PostMapping("/api/rest")
//    @ResponseBody
//    public Object restPost(@RequestParam(required = false, defaultValue = "Alice") String name,
//                           @RequestParam(required = false, defaultValue = "0") int value) {
//        Map<String, String> map = new HashMap<>();
//        map.put("name", name);
//        map.put("attackDamage", value + "");
//        map.put("method", "POST");

//        return map;
//    }

//    /**
//     * http://localhost:8080/api/rest
//     */
//    @PutMapping("/api/rest")
//    @ResponseBody
//    public Object restPut(@RequestBody String json) {
//        return json;
//    }

//    /**
//     * http://localhost:8080/api/rest
//     */
//    @DeleteMapping("/api/rest")
//    @ResponseBody
//    public Object restDelete() throws InterruptedException {
//        Map<String, String> map = new HashMap<>();
//        map.put("method", "DELETE");

//        Thread.sleep(2000);

//        return map;
//    }

//    @PostMapping("/api/upload")
//    @ResponseBody
//    public Object uploadFile(@RequestParam MultipartFile file,
//                             @RequestParam(required = false, defaultValue = "Alice") String name) throws IOException {
//        FileUtils.copyInputStreamToFile(file.getInputStream(), new File("/Users/Biao/Desktop/" + file.getOriginalFilename()));

//        Map<String, String> map = new HashMap<>();
//        map.put("name", name);
//        map.put("filename", file.getOriginalFilename());

//        return map;
//    }

//    @PostMapping("/api/uploads")
//    @ResponseBody
//    public Object uploadFiles(@RequestParam(name = "files") List<MultipartFile> files,
//                              @RequestParam(required = false, defaultValue = "Alice") String name) throws IOException {
//        List<String> filenames = new LinkedList<>();

//        for (MultipartFile file : files) {
//            FileUtils.copyInputStreamToFile(file.getInputStream(), new File("/Users/Biao/Desktop/" + file.getOriginalFilename()));
//            filenames.add(file.getOriginalFilename());
//        }

//        Map<String, Object> map = new HashMap<>();
//        map.put("name", name);
//        map.put("filenames", filenames);

//        return map;
//    }
//}

HE_CONTROL_END_NAMESPACE
