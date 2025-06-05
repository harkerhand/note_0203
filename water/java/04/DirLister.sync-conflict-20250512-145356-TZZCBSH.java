import java.io.File;
import java.util.*;
import java.util.regex.*;

/**
 * DirLister 是一个控制台应用程序，用于列出指定目录中具有指定后缀的文件，
 */
public class DirLister {

    /**
     * 主函数，读取用户输入并执行文件筛选与排序。
     * 
     * @param args 未使用的命令行参数
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.print("请输入目录路径（例如 C:\\\\Windows）：");
            String directoryPath = scanner.nextLine().trim();
            if (directoryPath.isEmpty())
                throw new IllegalArgumentException("目录路径不能为空！");

            System.out.print("请输入文件后缀名（例如 .log）：");
            String extension = scanner.nextLine().trim();
            if (!extension.startsWith("."))
                throw new IllegalArgumentException("后缀名必须以点(.)开头！");

            listAndSortFiles(directoryPath, extension);

        } catch (Exception e) {
            System.err.println("程序执行失败：" + e.getMessage());
        } finally {
            scanner.close();
        }
    }

    /**
     * 根据指定路径、扩展名和排序方式列出并排序文件。
     * 
     * @param dirPath   目录路径
     * @param extension 文件后缀名（例如 .log）
     */
    public static void listAndSortFiles(String dirPath, String extension) {
        File dir = new File(dirPath);

        if (!dir.exists()) {
            System.out.println("目录不存在！");
            return;
        }
        if (!dir.isDirectory()) {
            System.out.println("指定路径不是一个有效目录！");
            return;
        }

        String escapedExtension = Pattern.quote(extension);
        escapedExtension = escapedExtension.substring(2, escapedExtension.length() - 2);
        String regex = ".*" + escapedExtension.replace(".", "\\.") + "$";
        Pattern pattern = Pattern.compile(regex, Pattern.CASE_INSENSITIVE);

        File[] files = dir.listFiles((file) -> {
            if (!file.isFile())
                return false;
            String fileName = file.getName();
            boolean matches = pattern.matcher(fileName).matches();
            return matches;
        });

        if (files == null || files.length == 0) {
            System.out.println("没有找到匹配的文件！");
            return;
        }

        // 按最后修改时间排序
        Arrays.sort(files, (f1, f2) -> {
            long diff = f1.lastModified() - f2.lastModified();
            return Long.compare(0, diff);
        });

        // 输出结果
        System.out.println("排序后的文件列表（按最后修改时间排序）：");
        for (File file : files) {
            System.out.printf("%-40s 最后修改时间: %tc%n", file.getName(), file.lastModified());
        }
    }
}
