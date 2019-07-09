import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Homework {

    private static final int FIELD_HEIGHT = 12;
    private static final int FIELD_WIDTH = 8;
    private static final int B_FLAG = 1; // BLOCK FLAG
    private static final int E_FLAG = 0; // EMPTY FLAG
    private static final String EMPTY_FILED = ". ";

    private static final int[][][] BLOCKS_ARRARY = {{
                    {B_FLAG, B_FLAG, B_FLAG, B_FLAG},
            },{
                    {B_FLAG, B_FLAG, B_FLAG},
                    {E_FLAG, B_FLAG, E_FLAG},
            },{
                    {B_FLAG, B_FLAG, },
                    {B_FLAG, B_FLAG, },
            },{
                    {B_FLAG, B_FLAG, E_FLAG},
                    {E_FLAG, B_FLAG, B_FLAG},
            },{
                    {E_FLAG, B_FLAG, B_FLAG},
                    {B_FLAG, B_FLAG, E_FLAG},
            },{
                    {B_FLAG, B_FLAG, B_FLAG},
                    {E_FLAG, E_FLAG, B_FLAG},
            },{
                    {E_FLAG, E_FLAG, B_FLAG},
                    {B_FLAG, B_FLAG, B_FLAG},
            },
    };
    private static final Map<String, int[][]> BLOCK_MAP = new HashMap<String, int[][]>() {{
        String btypes[] = { "A","B","C","D","E","F","G" };
        for(int i = 0; i < BLOCKS_ARRARY.length; i++)
            put(btypes[i], BLOCKS_ARRARY[i]);
    }};
    private String[][] field = new String[FIELD_HEIGHT][FIELD_WIDTH];


    public Homework() {
        for (int i = 0; i < field.length; i++)
            for (int j = 0; j < field[i].length; j++)
                field[i][j] = EMPTY_FILED;
    }

    private void doGameSolution(String[] blocks) {
        for (String block : blocks) {
            System.out.println("====================\nnext = " + block);
            try {
                String blockType = block.substring(0, 1);
                int location = Integer.parseInt(block.substring(1, 2)) - 1;  // location to index

                makeTempField(blockType, location);
                printField();
                System.out.println("--------------------");

                makeResField(blockType, location);
                printField();
                System.out.println("====================");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("not enough space");
                break;
            }
        }
    }

    /*
     * 예외처리
     * 2차원 배열
     * 내장함수
     * 사용자 메서드 사용, 호출
     * */
    /*
     * 입력받은 값을 배열에 저장 메서드
     */
    public String[] parseInput(String input) {
        String[] InputArray = {};
        InputArray = input.trim().toUpperCase().replace(" ", "").replace("\"", "").split(",");
        return InputArray;
    }

    /*
     * 2차원 배열 출력 메서드
     */
    public void printField() {
        for (int i = 0; i < field.length; i++) {
            for (int j = 0; j < field[i].length; j++)
                System.out.print(field[i][j]);
            System.out.println();
        }
    }

    private void markBlock(String blockType, int blockShape[][], int y, int x) {
        for(int i = 0; i < blockShape.length; i++)
            for(int j = 0; j < blockShape[i].length; j++)
                if (blockShape[i][j] == B_FLAG)
                    field[y + i][x + j] = blockType + " ";
    }
    /*
     * makeTempField: 블록을 떨어뜨리기 전 필드배열 생성 메서드
     * 위치가 틀린 블럭은 들어오지 않는다.
     */
    public String[][] makeTempField(String blockType, int location) throws ArrayIndexOutOfBoundsException {
        int blockShape[][] = BLOCK_MAP.get(blockType);

        for(int i = 0; i < blockShape.length; i++)
            for(int j = 0; j < blockShape[i].length; j++)
                if (blockShape[i][j] == B_FLAG && field[0 + i][location + j] != EMPTY_FILED)
                    throw new ArrayIndexOutOfBoundsException("not enough space");

        markBlock(blockType, blockShape, 0, location);
        return field;
    }

    /*
     * makeResField : 블록 떨어뜨린 후 필드배열 생성 메서드
     * */
    public String[][] makeResField(String blockType, int location) {
        int blockShape[][] = BLOCK_MAP.get(blockType);

        // tempField 복구
        for(int i = 0; i < blockShape.length; i++)
            for(int j = 0; j < blockShape[i].length; j++)
                if (blockShape[i][j] == B_FLAG)
                    field[0 + i][location + j] = EMPTY_FILED;

        for (int y = 0; y < field.length; y++) {
            for (int i = 0; i < blockShape.length; i++) {
                for (int j = 0; j < blockShape[i].length; j++) {
                    if (blockShape[i][j] == B_FLAG && ( (y+i) >= field.length || field[y + i][location + j] != EMPTY_FILED) ) {
                        markBlock(blockType, blockShape, y - 1, location);
                        return field;
                    }
                }
            }
        }
        return field;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        Homework game = new Homework();

        String jum = sc.nextLine();

        String[] input = game.parseInput(jum);
        game.doGameSolution(input);
    }
}