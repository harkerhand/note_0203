import java.io.*;
import java.util.*;
import java.nio.file.*;

/**
 * 学生成绩管理器：实现将成绩保存到文件，读取、显示和添加记录功能。
 */
public class StudentScoresManager {

    private static String FILE_NAME = "scores.csv"; // 修改为非final以便可以更新
    private static int lastDisplayLineCount = 0; // 跟踪上次显示的行数

    /**
     * 主函数，展示初始化、读取与添加功能。
     * 
     * @param args 命令行参数（未使用）
     */
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            // 检查文件是否存在
            if (!Files.exists(Paths.get(FILE_NAME))) {
                System.out.println("成绩文件不存在，请提供文件路径：");
                FILE_NAME = getUserFilePath(scanner);
            }

            System.out.println("初始数据：");
            displayAllRecords(scanner);

            System.out.println("\n是否添加新记录？(y/n)：");
            if (scanner.nextLine().trim().equalsIgnoreCase("y")) {
                addNewRecord(scanner);
                System.out.println("\n添加后的数据：");
                displayAllRecords(scanner);
            }
        } catch (IOException e) {
            System.err.println("文件处理错误：" + e.getMessage());
        } finally {
            scanner.close();
        }
    }

    /**
     * 获取用户输入的文件路径
     * 
     * @param scanner 用于读取用户输入
     * @return 有效的文件路径
     */
    private static String getUserFilePath(Scanner scanner) {
        String filePath = "";
        while (true) {
            System.out.print("请输入文件路径（或按回车使用默认路径并创建新文件）：");
            filePath = scanner.nextLine().trim();

            // 如果用户未输入路径，使用默认路径
            if (filePath.isEmpty()) {
                try {
                    // 创建默认文件并写入标题行
                    File file = new File(FILE_NAME);
                    if (file.createNewFile()) {
                        try (BufferedWriter writer = new BufferedWriter(
                                new OutputStreamWriter(new FileOutputStream(FILE_NAME), "UTF-8"))) {
                            writer.write("学号,姓名,成绩\n");
                        }
                        System.out.println("已创建默认文件: " + FILE_NAME);
                    }
                    return FILE_NAME;
                } catch (IOException e) {
                    System.err.println("创建默认文件失败: " + e.getMessage());
                    continue;
                }
            }

            // 检查用户提供的文件路径
            File file = new File(filePath);
            if (file.exists()) {
                return filePath;
            } else {
                // 询问是否创建新文件
                System.out.print("文件不存在，是否创建新文件？(y/n): ");
                if (scanner.nextLine().trim().equalsIgnoreCase("y")) {
                    try {
                        if (file.createNewFile()) {
                            try (BufferedWriter writer = new BufferedWriter(
                                    new OutputStreamWriter(new FileOutputStream(filePath), "UTF-8"))) {
                                writer.write("学号,姓名,成绩\n");
                            }
                            System.out.println("已创建新文件: " + filePath);
                            return filePath;
                        }
                    } catch (IOException e) {
                        System.err.println("创建文件失败: " + e.getMessage());
                    }
                }
            }
        }
    }

    /**
     * 显示所有成绩记录，以表格格式输出。
     * 
     * @param scanner 用于读取用户输入（当文件不存在时）
     * @throws IOException 文件读取异常
     */
    private static void displayAllRecords(Scanner scanner) throws IOException {
        // 首先清除上一次显示的内容
        clearLastDisplay();

        // 检查文件是否存在
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            System.out.println("成绩文件不存在，请提供文件路径：");
            FILE_NAME = getUserFilePath(scanner);
        }

        List<String> outputLines = new ArrayList<>();
        outputLines.add("%-10s %-10s %-6s".formatted("学号", "姓名", "成绩"));
        outputLines.add("---------------------------");

        try (BufferedReader reader = new BufferedReader(
                new InputStreamReader(new FileInputStream(FILE_NAME), "UTF-8"))) {
            String line;
            reader.readLine(); // 跳过标题行
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split(",");
                if (parts.length == 3) {
                    outputLines.add("%-10s %-10s %-6s".formatted(parts[0], parts[1], parts[2]));
                }
            }
        }

        // 输出并记录行数
        for (String line : outputLines) {
            System.out.println(line);
        }
        lastDisplayLineCount = outputLines.size();
    }

    /**
     * 清除上一次显示的内容
     */
    private static void clearLastDisplay() {
        if (lastDisplayLineCount > 0) {
            // 移动光标到上一次显示的开始位置
            System.out.print("\033[" + lastDisplayLineCount + "A");
            // 清除从光标开始到屏幕结尾的内容
            System.out.print("\033[0J");
        }
    }

    /**
     * 添加新的学生成绩记录。
     * 
     * @param scanner 用于读取用户输入
     * @throws IOException 文件写入异常
     */
    private static void addNewRecord(Scanner scanner) throws IOException {
        // 检查文件是否存在
        File file = new File(FILE_NAME);
        if (!file.exists()) {
            System.out.println("成绩文件不存在，请提供文件路径：");
            FILE_NAME = getUserFilePath(scanner);
        }

        String id = "";
        while (true) {
            System.out.print("请输入学号：");
            id = scanner.nextLine().trim();
            if (!id.isEmpty() && id.matches("\\d+")) {
                break;
            }
            System.out.println("错误：学号必须是纯数字且不能为空！");
        }

        String name = "";
        while (true) {
            System.out.print("请输入姓名：");
            name = scanner.nextLine().trim();
            if (!name.isEmpty()) {
                break;
            }
            System.out.println("错误：姓名不能为空！");
        }

        String score = "";
        while (true) {
            System.out.print("请输入成绩：");
            score = scanner.nextLine().trim();
            try {
                float scoreValue = Float.parseFloat(score);
                if (scoreValue >= 0 && scoreValue <= 100) {
                    break;
                } else {
                    System.out.println("错误：成绩必须在0-100之间！");
                }
            } catch (NumberFormatException e) {
                System.out.println("错误：成绩必须是有效数字！");
            }
        }

        try (BufferedWriter writer = new BufferedWriter(
                new OutputStreamWriter(new FileOutputStream(FILE_NAME, true), "UTF-8"))) {
            writer.write(String.format("%s,%s,%s%n", id, name, score));
        }
    }
}
